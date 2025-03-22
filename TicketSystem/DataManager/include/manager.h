#pragma once

typedef MySQL::Connector CTOR;
namespace Manager
{	
	bool Init(const std::string& host,const std::string& user, const std::string& pass);
	bool Release();

	std::shared_ptr<CTOR> GetSQL();
}