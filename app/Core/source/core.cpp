#include "pch.h"
#include "core.h"
#include "database.h"
#include "manager.h"
namespace Core
{
	bool Init(const std::string& host, const std::string& user, const std::string& pass)
	{
		if (!MySQL::Init(host, user, pass))
			return false;
		return true;
	}
	bool Release()
	{
		if (!MySQL::Release())
			return false;
		return true;
	}
}