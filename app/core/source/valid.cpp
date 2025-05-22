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
		if (movie.releaseYear >= 1888 && movie.releaseYear <= 2025)
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
			if (!show.movieName.empty())
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
	bool LuhnCheck(const std::string& number)
	{
		int sum = 0;
		bool alternate = false;
		for (int i = number.length() - 1; i >= 0; i--) 
		{
			int n = number[i] - '0';
			if (alternate) {
				n *= 2;
				if (n > 9) n -= 9;
			}
			sum += n;
			alternate = !alternate;
		}
		return (sum % 10 == 0);
	}
}