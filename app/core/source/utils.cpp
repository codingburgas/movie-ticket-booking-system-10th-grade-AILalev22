#include "pch.h"
#include "utils.h"
#include <regex>

namespace Utils
{
	void Exit()
	{
		ErrMsg("Quiting!");
		exit(0);
	}
	void ErrMsg(const std::string& msg, int sec)
	{
		if (sec <= 0) sec = 1;

		Clear();
		std::cout << msg << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(sec));
		Clear();
	}
	void Clear()
	{
		system("cls"); 
	}

	void DbgMsg(const char* fmt, ...)
	{
#ifdef ON_DEBUG_STRINGS
		va_list va;
		va_start(va, fmt);

		char buf[512];
		vsprintf_s(buf, fmt, va); // print to variadic arg list

		OutputDebugStringA(buf);
		va_end(va);
#endif
	}
}