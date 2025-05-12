#include "pch.h"
namespace Manager
{
	// global db manager
	static std::shared_ptr<ManagerSQL> sql;

	ManagerSQL::ManagerSQL(const StruConnector& data)
	{
		isOK = true;

		ctor = std::make_shared<CTOR>(data.host, data.user, data.pass);
		if (!ctor->Connect() || !ctor->SetDB(data.schema)) isOK = false;
	}
	///////////
	std::shared_ptr<CTOR> GetSQL()
	{
		return sql->GetConnector();
	}
	bool Init(const std::string& host, const std::string& user, const std::string& pass, const std::string& schema)
	{
		StruConnector data = { host,user,pass,schema };
		if (sql = std::make_shared<ManagerSQL>(data))
		{
			if (sql->GetStatus()) // if manager is init correctly
			{
				Utils::DbgMsg("manager is ok");
				return true;
			}
		}
		Utils::DbgMsg("manager is not ok");
		return false;
	}
	void Release()
	{
		sql.reset();
	}
}