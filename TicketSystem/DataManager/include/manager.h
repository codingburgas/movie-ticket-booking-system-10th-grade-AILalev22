#pragma once

typedef MySQL::Connector CTOR;
namespace Manager
{	
	struct Account
	{
		std::string email;
		std::string password;
	};
	// init database
	bool Init(const std::string& host, const std::string& user, const std::string& pass);
	// release database
	bool Release();

	std::shared_ptr<CTOR>& GetSQL();
}