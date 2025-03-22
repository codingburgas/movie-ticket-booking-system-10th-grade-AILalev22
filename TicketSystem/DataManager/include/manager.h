#pragma once

typedef MySQL::Connector CTOR;
namespace Manager
{	
	struct Account
	{
		std::string username;
		std::string email;
		std::string password;
	};
	bool Init(const std::string& host,const Account& dbaccount);
	bool Release();

	std::shared_ptr<CTOR>& GetSQL();
}