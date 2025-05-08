#pragma once
#include <string>
namespace Entity
{
	struct Movie
	{
		// main info
		std::string name;
		std::string genre;
		int releaseYear;
		std::string language;

		Movie() : releaseYear(-1) {}
	};
	struct Show
	{
		// movie name
		std::string name;
		// date in YYYY-MM-DD HH:MM:SS format
		std::string date;
		// price
		double price;

		Show() : price(-1) {}
	};
    struct User
	{
		std::string email;
		std::string password;
	};
}
