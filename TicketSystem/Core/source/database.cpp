#ifndef _SQL
#define _SQL
#endif
#include "string.hpp"
#include "type.h"
#include "database.h"
#include <stdarg.h>
namespace MySQL
{
	//driver instance to mysql server
	static DRIVER* driver;
	// instance used to connect to database
	static CONN* conn;
	// instance used to execute direct queries
	static STMT* stmt;
	// instance used to get sets from select queries
	static RSET* rset;
	// instance used to build prepared statements and execute them
	static PSTMT* pstmt;

	bool Init()
	{
		driver = sql::mysql::get_mysql_driver_instance();;
		stmt = 0; pstmt = 0; conn = 0; rset = 0;
		return true;
	}
	bool Release()
	{
		if (stmt)
			delete stmt;
		if (pstmt)
			delete pstmt;
		if (conn)
			delete conn;
		if (rset)
			delete rset;
		return true;
	}
	Connector::Connector(const char* host, const char* user, const char* pass)
	{
		credentials[0] = host;
		credentials[1] = user;
		credentials[2] = pass;
	}
	bool Connector::Connect()
	{
		try
		{
			conn = driver->connect(credentials[0], credentials[1], credentials[2]);
		}
		catch (...)
		{
			if (conn)
				delete conn;
			return false;
		}
		return true;
	}
	void Connector::SetDB(const char* name)
	{
		try
		{
			conn->setSchema(name);
		}
		catch (...)
		{

		}
	}
	Connector::~Connector()
	{
		
	}

	void Connector::Write(const char* fmt, const char* query, ...)
	{
		int count = Str::Len(fmt);
		if (!fmt || !query || !count) return;
	
		pstmt = conn->prepareStatement(query);

		va_list va;
		va_start(va, query);

		int arg_d;
		double arg_f;
		const char* arg_s;
		uint arg_u;
		int i = 1;
		for (int j = 0; j < count; j++)
		{
			switch (*fmt)
			{
			case 'd':arg_d = va_arg(va, int); pstmt->setInt(i++, arg_d); break; // follow c-style format
			case 'f': arg_f = va_arg(va, double); pstmt->setDouble(i++, arg_f); break;
			case 's': arg_s = va_arg(va, const char*); pstmt->setString(i++, arg_s); break;
			case 'u': arg_u = va_arg(va, uint); pstmt->setUInt(i++, arg_u); break;
			}
			fmt++;
		}
		va_end(va);
		pstmt->executeUpdate();
	}
	char* Connector::Read(const char* fmt, const char* query)
	{
		char fmt2 = GetFormat(fmt);
		if (!fmt2) return 0;
		stmt = conn->createStatement();
		rset = stmt->executeQuery(query);
		Str::String conn_s;
		while(rset->next())
		{
			char buff[50] = { 0 };
			int read = 0;
			switch (fmt2)
			{
			case 'd': read = snprintf(buff, sizeof(buff), "%d", rset->getInt(1)); break; // read and append to String if matching any format
			case 'u': read = snprintf(buff, sizeof(buff), "%u", rset->getUInt(1)); break;
			case 'f': read = snprintf(buff, sizeof(buff), "%f", rset->getDouble(1)); break;
			case 's': conn_s.Append(rset->getString(1).c_str()); break;
			}

			if (read)
			{
				buff[read] = 0;
				conn_s.Append(buff);
			}
						
		}

		char* ret = (char*)Mem::Duplication(conn_s.Cstr(), conn_s.Size() + 1); // result str
		return ret;
	}
	char GetFormat(const char* fmt)
	{
		char possible[] = { 'd','u','s','f' };
		for (int i = 0; i < 4; i++)
		{
			if (Str::IndexOf(fmt, possible[i]) >= 0) return possible[i];
		}
		return 0;
	}
}