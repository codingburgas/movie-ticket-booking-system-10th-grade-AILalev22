#include "pch.h"
#include "valid.h"
namespace Validation
{
	bool IsValidUser(const Entity::User& acc)
	{
		std::regex patternPass(R"(^[a-zA-Z0-9]+$)");
		std::regex patternEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");

		return std::regex_search(acc.email, patternEmail) && std::regex_search(acc.password, patternPass) && acc.password.size() >= 8;
	}
}