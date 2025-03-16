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
	bool Connector::SetDB(const char* name)
	{
		try
		{
			conn->setSchema(name);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	Connector::~Connector()
	{
		
	}

	bool Connector::Write(const char* fmt, const char* query, ...)
	{
		int count = Str::Len(fmt);
		if (!fmt || !query || !count) return false;
	
		pstmt = conn->prepareStatement(query);

		va_list va;
		va_start(va, query);

		int arg_d;
		double arg_f;
		const char* arg_s;
		uint arg_u;
		int i = 1;
		while(count--)
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
		try
		{
			pstmt->executeUpdate();
		}
		catch (...)
		{
			return false;
		}
		return true;
	}

	
	char* Connector::Read(const char* fmt, const char* query)
	{
		char* fmt2 = TrimFormat(fmt);
		if (!fmt2) return 0;

		stmt = conn->createStatement();
		try
		{
			rset = stmt->executeQuery(query); // try executing query and if error, free fmt copy and stop
		}
		catch (...)
		{
			Mem::Free(fmt2);
			return 0;
		}

		Str::String res; //result with all retrived columns in each row
		int cols = Str::Len(fmt2);

		while (rset->next()) // itereate through each row of res set
		{
			char* tmpf = fmt2;
			int read = 0;
			char buff[50];
			for (int i = 1; i <= cols; i++)
			{
				switch (*tmpf++)
				{
				case 'd':case 'i': read = snprintf(buff, sizeof(buff), "%d", rset->getInt(i)); break; // read and append to String if matching any format
				case 'u': read = snprintf(buff, sizeof(buff), "%u", rset->getUInt(i)); break;
				case 'f': read = snprintf(buff, sizeof(buff), "%f", rset->getDouble(i)); break;
				case 's': read = snprintf(buff, sizeof(buff), "%s", rset->getString(i).c_str()); break;
				}
				if (read && i != cols)
				{
					buff[read] = ',';
					buff[read + 1] = 0;					
				}
				else
				{
					buff[read] = 0;
				}
				res.Append(buff);
			}
			if(!rset->isLast())
			res.PushBack('|');
		}

		Mem::Free(fmt2);
		char* ret = (char*)Mem::Duplication(res.Cstr(), res.Size() + 1); // result str copy
		return ret;
	}
	bool Find(const char* fmt, const char* query, char* val)
	{
		char fmt2 = GetFormat(fmt);
		if (!fmt2) return 0;
		stmt = conn->createStatement();
		rset = stmt->executeQuery(query);
		int len = Str::Len(val);

		while (rset->next())
		{
			char buff[50] = { 0 };
			int read = 0;
			switch (fmt2)
			{
			case 'd':case 'i': read = snprintf(buff, sizeof(buff), "%d", rset->getInt(1)); break; // read and later compare buffer with passed value
			case 'u': read = snprintf(buff, sizeof(buff), "%u", rset->getUInt(1)); break;
			case 'f': read = snprintf(buff, sizeof(buff), "%f", rset->getDouble(1)); break;
			case 's': read = snprintf(buff, sizeof(buff), "%s", rset->getString(1).c_str()); break;
			}

			if (read)
			{
				if (!Mem::Cmp(buff, val, len))
					return true;
			}
		}

		return false;
	}
	char GetFormat(const char* fmt)
	{
		char possible[] = { 'd','u','s','f','i'};
		for (int i = 0; i < 5; i++)
		{
			if (Str::IndexOf(fmt, possible[i]) >= 0) return possible[i];
		}
		return 0;
	}
	char* TrimFormat(const char* fmt)
	{
		if (!fmt) return 0;
		char buff[30];
		int i = 0;
		char possible[] = { 'd','i','f','s','u' };
		int len = Str::Len(fmt);

		while (*fmt)
		{
			if(Mem::IndexOf(possible, *fmt, sizeof(possible)) >= 0)
				buff[i++] = *fmt;
			fmt++;
		}
		buff[i++] = 0;
		char* ret = (char*)Mem::Alloc(i);

		Mem::Copy(ret, buff, i);
		return ret;
	}
}