#include "pch.h"
static std::shared_ptr<CTOR> ctor;

namespace Manager
{
	std::shared_ptr<CTOR>& GetSQL()
	{
		return ctor;
	}
	bool Init(const std::string& host, const Account& dbaccount)
	{
		if (!ctor.get())
		{
			ctor = std::make_shared<CTOR>(host, dbaccount.username, dbaccount.password);
			return ctor->Connect();
		}
		return false;
	}
	bool Release()
	{
		if (ctor)
		{
			ctor.reset();
			return true;
		}
		return false;
	}
}