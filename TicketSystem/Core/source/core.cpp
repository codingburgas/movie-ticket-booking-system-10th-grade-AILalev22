#include "core.h"
#include "database.h"
namespace Core
{
	bool Init()
	{
		if (!Mem::Init())
			return false;
		if (!MySQL::Init())
			return false;
		return true;
	}
	bool Release()
	{
		if (!Mem::Release())
			return false;
		if (!MySQL::Release())
			return false;
		return true;
	}
}