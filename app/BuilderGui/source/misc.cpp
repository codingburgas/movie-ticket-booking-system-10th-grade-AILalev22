#include "pch.h"
#include "misc.h"

namespace Misc
{
	std::string ToStr(const CString& s)
	{
		std::wstring ws = s.GetString();
		std::string stdStr(ws.begin(), ws.end());
		return stdStr;
	}
}