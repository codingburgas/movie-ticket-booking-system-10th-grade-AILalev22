#include "database.h"
#include "memory.h"
#include <stdarg.h>
#include "string.hpp"
namespace MySQL
{
	Connector::Connector(const char* host, const char* user, const char* pass) : driver(0),stmt(0),pstmt(0),conn(0),rset(0)
	{
		credentials[0] = host;
		credentials[1] = user;
		credentials[2] = pass;		
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
	Connector::~Connector()
	{
		Mem::Free(stmt);
		Mem::Free(rset);
		Mem::Free(conn);
		Mem::Free(pstmt);
	}
	void Connector::Write(int count, const char* format,const char* query, ...)
	{
		if (count <= 0 || !format || !query) return;
		pstmt = conn->prepareStatement(query);
		char* format2 = (char*)Mem::Duplication(format, Str::Len(format) + 1);
		TrimFormat(format2);
		for (int i = 1; i <= count; i++)
		{
			switch (*format)
			{
				// cases for each letter, %d %s %c %f %lu %u %zu, without %
				// exampel format str "dcff"
			}
			format++;
		}
		pstmt->executeUpdate();
		Mem::Free(format2);
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
			case 'c': buff[i++] = 'c'; break;
			case 's': buff[i++] = 's'; break;
			case 'u': buff[i++] = 'u'; break;
			default: break;
			}
			s++;
		}
		buff[i] = 0;
		Mem::Copy(fmt, buff, i + 1);
	}
}