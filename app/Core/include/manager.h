#pragma once

typedef MySQL::Connector CTOR;
//mysql db manager
namespace Manager
{	
	// init database manager
	bool Init(const std::string& host, const std::string& user, const std::string& pass);
	// release database manager
	bool Release();

	std::shared_ptr<CTOR>& GetSQL();
}