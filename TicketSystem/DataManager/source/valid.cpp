#include "pch.h"
#include "valid.h"
#include <regex>
namespace Validation
{
	bool IsValidEmail(const std::string& email)
	{
		std::regex pattern("(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$)");
		return std::regex_match(email, pattern);
	}
	bool IsValidPass(const std::string& pass)
	{
		if (pass.size() < 8) return false;
		
		char permited[] = { '"', '<', '>', '{', '}', '[', ']', '\\', '^', '`', '|', '/' };
		char forbidden[] = { '-', '_', '.', '~', '!', '$', '&', '(', ')', '*', '=', '+', ':', ';', '#' };
				
		int upper = 0, num = 0,special = 0;
		for (char c : pass)
		{
			for (char f : forbidden)
			{
				if (c == f)
				{
					return false;
				}
			}
			for (char p : permited)
			{
				if (special > 0) break;
				if (c == p)
				{
					special++;
					break;
				}
			}
			if (c >= 'A' && c <= 'Z')
			{
				upper++;
			}
			if (c >= '0' && c <= '9')
			{
				num++;
			}
		}
		if (num && upper && special)
		{
			return true;
		}
		return false;
	}
}