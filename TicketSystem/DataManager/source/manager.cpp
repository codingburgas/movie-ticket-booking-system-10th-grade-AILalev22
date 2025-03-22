#include "pch.h"
static std::shared_ptr<CTOR> ctor;

namespace Manager
{
	std::shared_ptr<CTOR>& GetSQL()
	{
		return ctor;
	}
	bool Init(const std::string& host, const std::string& user, const std::string& pass)
	{
		if (!ctor.get())
		{
			ctor = std::make_shared<CTOR>(host, user, pass);
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