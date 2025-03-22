#include "pch.h"
#include "core.h"
#include "database.h"
namespace Core
{
	bool Init()
	{
		if (!MySQL::Init())
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