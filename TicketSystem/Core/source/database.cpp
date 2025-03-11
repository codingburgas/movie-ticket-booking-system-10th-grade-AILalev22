#include "string.hpp"
#include "database.h"
#include "memory.h"
#include <stdarg.h>
namespace MySQL
{
	// main database connector
	static Connector* globalConn = nullptr;

	Connector::Connector(const char* host, const char* user, const char* pass) : driver(0),stmt(0),pstmt(0),conn(0),rset(0)
	{
		credentials[0] = host;
		credentials[1] = user;
		credentials[2] = pass;
		CreateDB("DATATICKET");
	}
	bool Connector::Connect()
	{
		driver = sql::mysql::get_mysql_driver_instance();
		conn = driver->connect(credentials[0], credentials[1], credentials[2]);
		return conn;
	}
	void Connector::SetDB(const char* name)
	{
		conn->setSchema(name);
	}
	void Connector::CreateDB(const char* name)
	{
		stmt = conn->createStatement();
		char query[50] = "CREATE DATABASE IF NOT EXISTS ";

		Mem::Copy(query + 30, name, Str::Len(name));

		stmt->execute(query);
	}
	Connector::~Connector()
	{
		if(stmt)
		Mem::Free(stmt);
		if(rset)
		Mem::Free(rset);
		if(conn)
		Mem::Free(conn);
		if(pstmt)
		Mem::Free(pstmt);
	}

	void Connector::Write(const char* fmt, const char* query, ...)
	{
		if (!fmt) return;
		char* fmt2 = (char*)Mem::Duplication(fmt, Str::Len(fmt) + 1);
		TrimFormat(fmt2);
		int count = Str::Len(fmt2);

		if (count <= 0 || !query)
		{
			Mem::Free(fmt2);
			return;
		}
		pstmt = conn->prepareStatement(query);

		va_list va;
		va_start(va, query);
		char* ftmp = fmt2;
		int arg_d;
		double arg_f;
		char* arg_s;
		uint arg_u;
		for (int i = 1; i <= count; i++)
		{
			switch (*ftmp)
			{
			case 'd':arg_d = va_arg(va, int); pstmt->setInt(i, arg_d); break;
			case 'f': arg_f = va_arg(va, double); pstmt->setDouble(i, arg_f); break;
			case 's': arg_s = va_arg(va, char*); pstmt->setString(i, arg_s); break;
			case 'u': arg_u = va_arg(va, uint); pstmt->setUInt(i, arg_u); break;
			}
			ftmp++;
		}
		va_end(va);
		pstmt->executeUpdate();
		Mem::Free(fmt2);
	}
	void* Connector::Read(const char* fmt, const char* query,Str::String& str)
	{
		if (!fmt) return 0;
		char* format2 = (char*)Mem::Duplication(fmt, Str::Len(fmt) + 1);
		TrimFormat(format2);
		int count = Str::Len(format2);

		if (count <= 0 || !query)
		{
			Mem::Free(format2);
			return 0;
		}
		stmt = conn->createStatement();
		stmt->executeQuery(query);
		char* ftmp = format2;
		for (int i = 1; i <= count; i++)
		{
			if (rset->next())
			{
				char buff[10];
				int t = 0;
				switch (*ftmp)
				{
				case 'd': t = snprintf(buff, sizeof(buff), "%d", rset->getInt(i)); break; 				
				case 'u': t = snprintf(buff, sizeof(buff), "%u", rset->getUInt(i)); break;
				case 'f': t = snprintf(buff, sizeof(buff), "%f", rset->getDouble(i)); break;
				case 's': str.Append(rset->getString(i).c_str()); break;
				}

				if (t)
				{
					buff[t] = 0;
					str.Append(buff);
				}
				ftmp++;
			}
		}
		return (void*)str.Cstr();
	}
	void TrimFormat(char* fmt)
	{
		if (!fmt) return;
		char buff[50];
		int i = 0;
		char* s = fmt;
		while (*s)
		{
			switch (*s)
			{
			case 'd': buff[i++] = 'd'; break;
			case 'f': buff[i++] = 'f'; break;
			case 's': buff[i++] = 's'; break;
			case 'u': buff[i++] = 'u'; break;
			}
			s++;
		}
		buff[i] = 0;
		Mem::Copy(fmt, buff, i + 1);
	}
}