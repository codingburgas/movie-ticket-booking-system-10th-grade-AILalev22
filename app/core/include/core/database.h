#pragma once
#include <string>
namespace MySQL
{
	class Connector
	{
		// database connect credentials
		 std::string credentials[3];

		 //set mysql instances
		 void Init();
		 //release mysql instances
		 void Release();
	public:
		Connector(const std::string& host, const std::string& user, const std::string& pass);
		~Connector();

		// set the database to use
		bool SetDB(const std::string& name);
		//connect to the mysql server
		bool Connect();

		// get data from multiple columns with a select query and C format
		bool Read(std::string fmt, const std::string& query, std::string& dst);
		// insert values with a insert into query with C format
		bool Write(std::string fmt, const std::string& query, ...);
		// executes all types of queries
		bool Query(const std::string& query);
	};
	// trim c-style format
	// "%d %f" -> "df"
	void TrimFormat(std::string& fmt);
}