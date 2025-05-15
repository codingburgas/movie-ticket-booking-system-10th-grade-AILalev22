#include "pch.h"
#include "valid.h"
#include <regex>
namespace Validation
{
	bool IsValidUser(const Entity::User& acc)
	{
		std::regex patternEmail(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
		std::regex patternPass(R"(^[a-zA-Z0-9]+$)");

		return std::regex_search(acc.email, patternEmail) && std::regex_search(acc.password, patternPass) && acc.password.size() >= 8;
	}
	bool IsValidMovie(const Entity::Movie& movie)
	{
		if (movie.releaseYear >= 1900 && movie.releaseYear <= 2025)
		{
			if (!movie.genre.empty())
			{
				if (!movie.name.empty())
				{
					return true; // if all criteria is met
				}
			}
		}
		return false;
	}
	bool IsValidShow(const Entity::Show& show)
	{
		if (!show.date.empty())
		{
			if (!show.name.empty())
			{
				if (show.price > 0)
				{
					return true;
				}
			}
		}
		return false;
	}
	bool IsValidSmtp(const std::string& addr)
	{
		std::regex pattern(R"(smtps?:\/\/[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
		return std::regex_search(addr, pattern);
	}
}