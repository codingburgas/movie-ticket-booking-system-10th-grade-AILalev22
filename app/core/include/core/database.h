#pragma once
#include <string>
namespace MySQL
{
	class Connector
	{
		// host,user,pass db connect credentials
		 std::string credentials[3];

	public:
		Connector(const std::string& host, const std::string& user, const std::string& pass);
		~Connector();

		// set the schema to use
		bool SetDB(const std::string& schema) const;
		//connect to the mysql server
		bool Connect() const;

		// get data from multiple columns with a select query and C format
		bool Read(std::string fmt, const std::string& query, std::string& dst) const;
		// insert values with a insert into query with C format
		bool Write(std::string fmt, const std::string& query, va_list va) const;
		// executes all types of queries
		bool Query(const std::string& query) const;
		// set db connect credentials
		void SetCredentials(const std::string& host, const std::string& user, const std::string& pass);
	};
}