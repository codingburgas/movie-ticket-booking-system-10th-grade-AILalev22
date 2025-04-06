#include "pch.h"
#include "present.h"
#include "core.h"
//#include "access.h"

namespace Present
{
	bool Init(const std::string& host, const std::string& user, const std::string& pass)
	{
		if(!Core::Init(host,user,pass))
			return false;
		return true;
	}
	bool Release()
	{
		if (!Core::Release())
			return false;
		return true;
	}
}