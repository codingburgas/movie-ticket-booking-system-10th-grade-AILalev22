#pragma once

typedef MySQL::Connector CTOR;
namespace Manager
{	
	//mysql db manager
	class ManagerSQL
	{
		std::shared_ptr<CTOR> ctor;
		// true if schema is set and connector is connected
		bool isOK;
	public:
		// init db manager
		ManagerSQL(const std::string& host, const std::string& user, const std::string& pass, const std::string& schema);

		// returns manager status
		bool GetStatus()
		{
			return isOK;
		}
		// returns mysql connector
		std::shared_ptr<CTOR> GetConnector() { return ctor; }
	};

	// get global mysql connector
	std::shared_ptr<CTOR> GetSQL();

	// init global db manager
	bool Init(const std::string& host, const std::string& user, const std::string& pass, const std::string& schema);
	// release global db manager
	void Release();
}