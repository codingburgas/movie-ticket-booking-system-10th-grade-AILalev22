#pragma once

typedef MySQL::Connector CTOR;
namespace MySQL
{	
	// init database manager
	bool InitManager(const std::string& host, const std::string& user, const std::string& pass);
	// release database manager
	bool ReleaseManager();

	std::shared_ptr<CTOR>& GetSQL();
}