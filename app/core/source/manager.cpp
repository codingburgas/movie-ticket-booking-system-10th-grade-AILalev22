#include "pch.h"
namespace Manager
{
	// global db manager
	static std::shared_ptr<ManagerSQL> sql;

	ManagerSQL::ManagerSQL(const std::string& host, const std::string& user, const std::string& pass, const std::string& schema)
	{
		isOK = true;

		ctor = std::make_shared<CTOR>(host, user, pass);
		if (!ctor->Connect() || !ctor->SetDB(schema)) isOK = false;		
	}
	///////////
	std::shared_ptr<CTOR> GetSQL()
	{
		return sql->GetConnector();
	}
	bool Init(const std::string& host, const std::string& user, const std::string& pass, const std::string& schema)
	{
		if (sql = std::make_shared<ManagerSQL>(host, user, pass, schema))
		{
			Utils::DbgMsg("manager is ok");
			return true;
		}
		Utils::DbgMsg("manager is not ok");
		return false;
	}
	void Release()
	{
	}
}