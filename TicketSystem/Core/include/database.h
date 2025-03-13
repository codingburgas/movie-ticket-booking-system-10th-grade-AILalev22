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
		void CreateDB(const char* name);
		void SetDB(const char* name);
		bool Connect();
		char* Read(const char* fmt, const char* query);
		void Write(const char* fmt, const char* query, ...);
	};

	// set mysql connector instances
	bool Init();
	//release mysql connector instances
	bool Release();
}