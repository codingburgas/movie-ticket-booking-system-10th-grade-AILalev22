#include "pch.h"
#include "database.h"
#include "manager.h"
namespace MySQL
{
	static std::shared_ptr<CTOR> ctor;

	std::shared_ptr<CTOR>& GetSQL()
	{
		return ctor;
	}
	bool InitManager(const std::string& host, const std::string& user, const std::string& pass)
	{
		if (!ctor.get())
		{
			ctor = std::make_shared<CTOR>(host, user, pass);
			return ctor->Connect();
		}
		else
		{
			if (ReleaseManager())
			{
				InitManager(host, user,pass);
			}
		}
		return false;
	}
	bool ReleaseManager()
	{
		if (ctor)
		{
			ctor.reset();
			return true;
		}
		return false;
	}
}