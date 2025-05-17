#include "pch.h"
#include "utils.h"

namespace Utils
{
	void Exit()
	{
		ErrMsg("Quiting!");
		ExitProcess(0);
	}
	void ErrMsg(const std::string& msg, int sec)
	{
		if (sec <= 0) sec = 1;

		Clear();
		std::cout << msg << std::endl;
		Sleep(sec * 1000);
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

		char buf[512] = { 0 };
		vsprintf_s(buf, fmt, va); // print to buf fmt and args after fmt

		size_t len = strlen(buf);
		if (len <= sizeof(buf) - 2)
		{
			buf[len] = '\n';
			buf[len + 1] = 0;
		}
		else
			buf[len] = 0;

		OutputDebugStringA(buf);
		va_end(va);
#endif
	}
	void Trim(std::string& src,const std::string& chars, bool possible)
	{
		std::string buff;

		for (const auto& c : src)
		{
			bool isIn = chars.find(c) != std::string::npos;

			if ((possible && isIn) || (!possible && !isIn))
			{
				buff.push_back(c);
			}
		}
		src = buff;
	}
}