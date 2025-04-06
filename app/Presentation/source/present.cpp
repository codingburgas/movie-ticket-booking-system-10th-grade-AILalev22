#include "pch.h"
#include "present.h"
#include "core.h"
//#include "access.h"

namespace Present
{
	bool Init()
	{
		/*if(!Core::Init())
			return false;*/
		return true;
	}
	bool Release()
	{
		if (!Core::Release())
			return false;
		return true;
	}
}