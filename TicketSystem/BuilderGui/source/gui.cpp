#include "pch.h"
#include "menu.h"

namespace Gui
{
	bool Init()
	{
		if (!Menu::Init())
			return false;
		return true;
	}
	bool Release()
	{
		if (!Menu::Release())
			return false;
		return true;
	}
}