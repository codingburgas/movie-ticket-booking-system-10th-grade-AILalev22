#include "pch.h"
namespace Manager
{
	// global db manager
	static std::shared_ptr<ManagerSQL> sql;

	ManagerSQL::ManagerSQL(const std::string& host, const std::string& user, const std::string& pass, const std::string& dbdata)
	{
		isOK = true;

		ctor = std::make_shared<CTOR>(host, user, pass);
		if(!ctor->Connect() || !ctor->SetDB(dbdata)) isOK = false;
	
	}
	ManagerSQL::~ManagerSQL()
	{
	}
	///////////
	std::shared_ptr<CTOR> GetSQL()
	{
		return sql->GetConnector();
	}
	bool Init(const std::string& host, const std::string& user, const std::string& pass, const std::string& dbdata)
	{
		if (sql = std::make_shared<ManagerSQL>(host,user,pass,dbdata))
			return true;
		return false;
	}
	void Release()
	{
	}
}