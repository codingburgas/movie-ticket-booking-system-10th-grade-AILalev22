#include "pch.h"
#include "misc.h"
#include <regex>
#include <conio.h>

namespace Misc
{
	void EnterNumber(std::string& num, bool floating)
	{
		int cdot = 0; // floating point count
		while (true)
		{
			std::cout << ":";
			std::cin >> num;

			if (floating)
			{
				if (std::all_of(num.begin(), num.end(), [&cdot](char c) {if (c == '.') { cdot++; return 1; } return isdigit(c); }))
				{
					if (!(cdot > 1 || num[0] == '.' || num[num.size() - 1] == '.'))
					{
						try
						{
							if (std::stof(num) > 0)
								break;// break if num is a non-negative floating point number
						}
						catch (...)
						{

						}
					}
					cdot = 0;
				}
			}
			else
			{
				if (std::all_of(num.begin(), num.end(), isdigit))
					if (std::stod(num) > 0)
						break; // break if num is a negative integer
			}
		}
		Utils::Clear();
	}
	void EnterDateTime(std::string& date)
	{
		std::regex pattern(R"(^\d{4}-\d{2}-\d{2} \d{2}:\d{2}:\d{2}$)");
		do
		{
			std::cout << ':';
			std::getline(std::cin, date);
		} while (!std::regex_match(date, pattern));
		Utils::Clear();
	}
	void EnterMovieData(Entity::Movie& movie)
	{
		std::cout << "Enter movie's name\n:";
		std::cin >> movie.name;

		std::cout << "Enter movie's genre\n:";
		std::cin >> movie.genre;

		std::cout << "Enter movie's release year\n";
		std::string num;
		EnterNumber(num);

		std::cout << "Enter movie's language\n:";
		std::cin >> movie.language;

		movie.releaseYear = std::stoi(num);
		Utils::Clear();
	}
	void EnterShowData(Entity::Show& show)
	{
		std::cout << "Enter show name\n:";
		std::cin >> show.name;

		std::cout << "Enter show date in YYYY-MM-DD HH:MM:SS format\n:";
		EnterDateTime(show.date);

		std::cout << "Enter price\n:";
		std::string price;
		EnterNumber(price, true);
		show.price = std::stof(price);

		Utils::Clear();
	}
	void EnterUserPassword(Entity::User& user)
	{
		std::string& pass = user.password;
		char c;

		std::cout << "\nEnter password\n:";

		while (true)
		{
			c = _getch();

			if (c == 13) // enter
				break;
			if (c == 8) //back
			{
				if (!pass.empty()) 
				{
					pass.pop_back();
					std::cout << "\b \b";
				}
			}
			else if (isprint(c)) // if is num,symbol,letter
			{
				pass.push_back(c);
				std::cout << '*';
			}
		}
	}
	//void EnterMovieCinema(Entity::Movie& movie)
	//{
	//	std::cout << "Enter movie's cinema:\n1. CinemaVarna\n2. CinemaBurgas\n";
	//	std::string choice;
	//	do
	//	{
	//		std::cout << ':';
	//		std::cin >> choice;
	//	} while (choice != "1" && choice != "2");
	//	
	//	//.cinemaName = choice == "1" ? "CinemaVarna" : "CinemaBurgas";	
	//}
}