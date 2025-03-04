#include "../include/core.h"
namespace Core
{
	bool Init()
	{
		if (!Mem::Init())
			return false;
		return true;
	}
	bool Release()
	{
		if (!Mem::Release())
			return false;
		return true;
	}
}