#pragma once
#ifdef _CORE
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/exception.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
typedef sql::PreparedStatement PSTMT;
typedef sql::ResultSet RSET;
typedef sql::Statement STMT;
typedef sql::Connection CONN;
typedef sql::mysql::MySQL_Driver DRIVER;
#endif
typedef unsigned char byte;
typedef unsigned int uint;

