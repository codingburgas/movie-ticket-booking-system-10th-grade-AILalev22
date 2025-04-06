#include "pch.h"
#include "menu.h"
#include "present.h"
#include "caption.h"

namespace Menu
{
	void Main()
	{
		if (!Present::Init())
		{
			Misc::Exit(); // exit if init fails
		}
		AuthMenu();
		MainMenu();

		if (!Present::Release())
		{
		}

		Misc::Exit(); // exit with quiting msg when program finishes
	}
	void AuthMenu()
	{
		Caption::PrintCaption();
	}
	void MainMenu()
	{

	}
}