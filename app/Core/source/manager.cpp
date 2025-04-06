#include "pch.h"
#include "database.h"
#include "manager.h"
namespace Manager
{
	static std::shared_ptr<CTOR> ctor;

	std::shared_ptr<CTOR>& GetSQL()
	{
		return ctor;
	}
	bool Init(const std::string& host, const std::string& user, const std::string& pass)
	{
		if (!ctor.get())
		{
			ctor = std::make_shared<CTOR>(host, user, pass);
			if (!ctor->Connect()) return false; // if connecting fails return false

			return ctor->SetDB("dataticket");
		}
		else
		{
			if (Release())
			{
				Init(host, user,pass);
			}
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