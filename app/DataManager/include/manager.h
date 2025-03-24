#pragma once

typedef MySQL::Connector CTOR;
namespace Manager
{	
	// init database
	bool Init(const std::string& host, const std::string& user, const std::string& pass);
	// release database
	bool Release();

	std::shared_ptr<CTOR>& GetSQL();
}