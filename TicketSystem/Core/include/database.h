#pragma once
namespace MySQL
{
	class Connector
	{
		// database connect credentials
		const char* credentials[3];
	public:
		Connector(const char* host, const char* user, const char* pass);
		~Connector();
		// set the database to use
		bool SetDB(const char* name);
		//connect to the mysql server
		bool Connect();
		// get data from a single column with a select query and C format
		char* Read(const char* fmt, const char* query);
		// insert values with a insert into query with C format
		bool Write(const char* fmt, const char* query, ...);
	};

	// set mysql connector instances
	bool Init();
	//release mysql connector instances
	bool Release();
	// trim c-style format
	// "%d %f" -> "df"
	char* TrimFormat(const char* fmt);
}