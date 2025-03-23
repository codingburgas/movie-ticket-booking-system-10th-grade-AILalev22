#include "pch.h"
#include "valid.h"
#include <regex>
namespace Validation
{
	bool IsValidAccount(const Manager::Account& acc)
	{
		return IsValidEmail(acc.email) && IsValidPass(acc.password);
	}
	bool IsValidEmail(const std::string& email)
	{
		std::regex pattern("(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$)");
		return std::regex_match(email, pattern);
	}
	bool IsValidPass(const std::string& pass)
	{
		if (pass.size() < 8) return false;
				
		std::regex num("([0-9])"), upper("([A-Z])"), forbidden("([-_.~!$ & () *= +:; #])"), permited(R"([\"<>{}\[\]\\^`|/])");

		if (std::regex_match(pass, num) && std::regex_match(pass, upper) && std::regex_match(pass, permited) && !std::regex_match(pass, forbidden))
			return false;
		return true;
	}
}