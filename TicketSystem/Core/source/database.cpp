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
		driver = sql::mysql::get_mysql_driver_instance();
		stmt = 0; pstmt = 0; conn = 0; rset = 0;
		return driver;
	}
	bool Release()
	{
		if (driver)
			delete driver;
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
			case 'd':arg_d = va_arg(va, int); pstmt->setInt(i++, arg_d); break;
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
		int count = Str::Len(fmt);
		if (!fmt || !query || !count) return 0;
		
		stmt = conn->createStatement();
		stmt->executeQuery(query);
		Str::String conn_s;
		int i = 1;
		for (int j = 0; j < count; j++)
		{
			if (rset->next())
			{
				char buff[50];
				int read = 0;
				switch (*fmt)
				{
				case 'd': read = snprintf(buff, sizeof(buff), "%d", rset->getInt(i++)); break;
				case 'u': read = snprintf(buff, sizeof(buff), "%u", rset->getUInt(i++)); break;
				case 'f': read = snprintf(buff, sizeof(buff), "%f", rset->getDouble(i++)); break;
				case 's': conn_s.Append(rset->getString(i++).c_str()); break;
				}

				if (read)
				{
					buff[read] = 0;
					conn_s.Append(buff);
				}
				fmt++;
			}
		}

		char* ret = (char*)Mem::Duplication(conn_s.Cstr(), conn_s.Size() + 1);
		return ret;
	}
}