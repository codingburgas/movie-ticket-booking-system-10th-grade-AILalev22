#include "pch.h"
#ifndef SQL
#define SQL
#endif
#include "database.hpp"
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include "memory.hpp"
#include "type.hpp"
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
		stmt = nullptr; pstmt = nullptr; conn = nullptr; rset = nullptr;
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
	Connector::Connector(const std::string& host, const std::string& user, const std::string& pass)
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
	bool Connector::SetDB(const std::string& name)
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
	bool Connector::Query(const std::string& query)
	{
		try
		{
			stmt = conn->createStatement();
			stmt->execute(query);
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
	bool Connector::Write(std::string fmt, const std::string& query, ...)
	{
		size_t len = fmt.size();
		if (fmt.empty() || query.empty() || len == 0) return false;
	
		try
		{
			pstmt = conn->prepareStatement(query);
		}
		catch (...)
		{
			return false;
		}
		va_list va;
		va_start(va, query.c_str());

		int i = 1;
		int arg_d;
		double arg_f;
		std::string* arg_s;
		uint arg_u;
		while(len--)
		{
			switch (fmt.front())
			{
			case 'd':arg_d = va_arg(va, int); pstmt->setInt(i++, arg_d); break; // follow c-style format
			case 'f': arg_f = va_arg(va, double); pstmt->setDouble(i++, arg_f); break;
			case 's': arg_s = va_arg(va, std::string*); pstmt->setString(i++,*arg_s); break;
			case 'u': arg_u = va_arg(va, uint); pstmt->setUInt(i++, arg_u); break;
			}
			fmt.erase(0, 1);
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

	
	void Connector::Read(std::string fmt, const std::string& query,std::string& dst)
	{
		TrimFormat(fmt);
		if (fmt.empty()) return;

		stmt = conn->createStatement();
		try
		{
			rset = stmt->executeQuery(query); // try executing query and if error, free fmt copy and stop
		}
		catch (...)
		{
			return;
		}

		size_t cols = fmt.size();
		
		while (rset->next()) // itereate through each row of res set
		{
			std::string fmt2 = fmt;		
			for (size_t i = 1; i <= cols; i++)
			{
				std::string buff;
				switch (fmt2.front())
				{
				case 'd': case 'i': buff = std::to_string(rset->getInt(i)); break;
				case 'f': buff = std::to_string(rset->getDouble(i)); break;
				case 'u': buff = std::to_string(rset->getUInt(i)); break;
				case 's': buff = rset->getString(i); break;
				}
				if (!buff.empty() && i != cols)
				{
					buff.push_back(',');
				}
				fmt2.erase(0, 1);
				dst.append(buff);
			}
			if(!rset->isLast() || rset->isFirst() && rset->isLast())
			dst.push_back('|');
		}

	}
	void TrimFormat(std::string& fmt)
	{
		if (fmt.empty()) return;
		std::string new_fmt;
		char possible[] = { 'd','i','f','s','u' };
		size_t len = sizeof(possible);

		for (char c : fmt)
		{
			for (size_t i = 0; i < len; i++)
			{
				if (c == possible[i])
				{
					new_fmt.push_back(possible[i]);
					break;
				}
			}
		}
		fmt = new_fmt;
	}
}