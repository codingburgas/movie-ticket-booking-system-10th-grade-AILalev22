#include "pch.h"
#include "manager.h"
#include "valid.h"
namespace Manager
{
	// global db manager
	static std::shared_ptr<ManagerSQL> sql;
	// global smtp request manager
	static std::shared_ptr<ManagerSMTP> smtp;

	void ManagerSQL::Init()
	{
		if (!inst->Connect() || !inst->SetDB(dataInst.schema)) isOK = false;
	}
	void ManagerSMTP::Init()
	{
		if(!Validation::IsValidSmtp(dataInst.smtpAddr)) isOK = false;
	}
	///////////
	std::shared_ptr<ManagerSQL> GetSQL()
	{
		return sql;
	}
	std::shared_ptr<ManagerSMTP> GetSMTP()
	{
		return smtp;
	}
	bool Init(const StruConnector& ctorInit,const StruSMTP& smtpInit)
	{
		bool ret = true;
		if ((sql = std::make_shared<ManagerSQL>(ctorInit)) && (smtp = std::make_shared<ManagerSMTP>(smtpInit)))
		{
			sql->Init();
			smtp->Init();
			if (!sql->GetStatus()) // if managers are not init correctly
			{
				DbgMsg("managerSQL is not ok");
				ret = false;
			}
			if (!smtp->GetStatus())
			{
				DbgMsg("managerSMTP is not ok");
				ret = false;
			}
		}
		else
			ret = false;
		return ret;
	}
	void Release()
	{
		sql.reset();
		smtp.reset();
	}
}