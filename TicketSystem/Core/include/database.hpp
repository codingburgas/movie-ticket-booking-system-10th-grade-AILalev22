#pragma once
#include <string>
namespace MySQL
{

	class Connector
	{
		// database connect credentials
		 std::string credentials[3];

	public:
		Connector(const std::string& host, const std::string& user, const std::string& pass);
		~Connector() = default;

		// set the database to use
		bool SetDB(const std::string& name);
		//connect to the mysql server
		bool Connect();

		// get data from a single column with a select query and C format
		void Read(std::string fmt, const std::string& query, std::string& dst);
		// insert values with a insert into query with C format
		bool Write(std::string fmt, const std::string& query, ...);
		// executes all types of queries
		bool Query(const std::string& query);
	};

	// set mysql connector instances
	bool Init();
	//release mysql connector instances
	bool Release();
	// trim c-style format
	// "%d %f" -> "df"
	void TrimFormat(std::string& fmt);
}