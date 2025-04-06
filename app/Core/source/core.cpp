#include "pch.h"
#include "core.h"
#include "database.h"
#include "manager.h"
namespace Core
{
	bool Init(const std::string& host, const std::string& user, const std::string& pass)
	{
		if (!Manager::Init(host, user, pass))
			return false;
		return true;
	}
	bool Release()
	{
		if (!Manager::Release())
			return false;
		return true;
	}
}