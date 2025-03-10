#pragma once
#include "type.h"
namespace MySQL
{
	class Connector
	{
		//driver instance to our mysql server
		DRIVER* driver;
		// instance used to connect to database
		CONN* conn;
		// instance used to execute direct queries
		STMT* stmt;
		// instance used to get sets from select queries
		RSET* rset;
		// instance used to build prepared statements and execute them
		PSTMT* pstmt;
		// database connect credentials
		const char* credentials[3];
	public:
		Connector(const char* host, const char* user, const char* pass);
		~Connector();
		void SetDB(const char* name);
		void Write( const char* format, const char* query, ...);
		bool Connect();
	};

	// get format without % and spaces
	// "%d %c %f" -> "dcf"
	void TrimFormat(char* fmt);
}