#include "pch.h"
#include "core.hpp"
#include "database.hpp"
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