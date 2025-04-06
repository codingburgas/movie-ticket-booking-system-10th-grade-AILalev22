#include "pch.h"
#include "misc.h"
#include <windows.h>

namespace Misc
{
	void Exit()
	{
		ErrMsg("Quiting!");
		exit(0);
	}
	void ErrMsg(const std::string& msg)
	{
		Clear();
		std::cout << msg << std::endl;
		Sleep(500);
		Clear();
	}
	void Clear()
	{
		system("cls"); 
	}
}