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
		void SetDB(const char* name);
		//connect to the mysql server
		bool Connect();
		// get data with a select query and C format
		char* Read(const char* fmt, const char* query);
		// insert values with a insert into query with C format
		void Write(const char* fmt, const char* query, ...);
	};

	// set mysql connector instances
	bool Init();
	//release mysql connector instances
	bool Release();
	char GetFormat(const char* fmt);
}