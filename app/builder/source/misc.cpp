#include "pch.h"
#include "misc.h"
#include <regex>
#include <conio.h>
#include <iomanip>
#include "main.h"
#include "core\crud.h"
namespace Misc
{
	void EnterNumber(std::string& num, bool floating)
	{
		int cdot = 0; // floating point count
		for (;;)
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
							Utils::DbgMsg("error stof()");
						}
					}
					cdot = 0;
				}
			}
			else
			{
				if (std::all_of(num.begin(), num.end(), isdigit))
					try
					{
						if (std::stod(num) > 0)
							break;// break if num is a non-negative number
					}
					catch (...)
					{
						Utils::DbgMsg("error stod()");
					}
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

		Utils::Clear();
		std::cout << "Enter movie's genre\n:";
		std::cin >> movie.genre;
		Utils::Clear();

		std::cout << "Enter movie's release year\n";
		std::string num;
		EnterNumber(num);

		std::cout << "Enter movie's language\n:";
		std::cin >> movie.language;

		movie.releaseYear = std::stoi(num);
		Utils::Clear();
	}
	bool EnterShowData(Entity::Show& show)
	{
		std::cout << "Enter movie's name\n:";
		std::cin >> show.movieName;

		Utils::Clear();
		std::string dstData;
		if (!Select::SelectMovie(dstData,show.movieName))
		{
			Utils::ErrMsg("Movie does not exist"); // if movie doesn't exists, cannot add show for it
			return false;
		}
		std::cout << "Enter show date in YYYY-MM-DD HH:MM:SS format\n";
		getchar();

		EnterDateTime(show.date);

		Utils::Clear();

		std::cout << "Enter price\n:";
		std::string price;
		EnterNumber(price, true);
		show.price = std::stof(price);

		Utils::Clear();

		std::cout << "Choose show's cinema:\n1. CinemaBurgas\n2. CinemaVarna\n";
		std::string choice;
		do
		{
			std::cout << ':';
			std::cin >> choice;
		} while (choice != "1" && choice != "2");

		show.cinemaName = choice == "1" ? "CinemaBurgas" : "CinemaVarna";

		Utils::Clear();
		return true;
	}
	void EnterUserPassword(Entity::User& user)
	{
		std::string& pass = user.password;
		char c;

		std::cout << "\nEnter password\n:";

		for (;;)
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
	void PrintStrTok(std::string op, char delim, const std::string fields[], int c_fields, const int colWidths[])
	{
		int totalWidth = 0;
		for (int i = 0; i < c_fields; ++i)
			totalWidth += colWidths[i] + 1;
		totalWidth += 1;

		std::cout << std::string(totalWidth, '-') << std::endl;

		std::cout << "|";
		for (int i = 0; i < c_fields; i++)
		{
			std::cout << std::setw(colWidths[i]) << std::left << fields[i] << "|";
		}
		std::cout << std::endl;

		std::cout << std::string(totalWidth, '-') << std::endl;

		auto PrintRow = [&](const std::string& row)
			{
				size_t start = 0, end;
				int column = 0;

				std::cout << "|";
				while ((end = row.find(',', start)) != std::string::npos && column < c_fields)
				{
					std::cout << std::setw(colWidths[column]) << std::left << row.substr(start, end - start) << "|";
					start = end + 1;
					column++;
				}
				if (column < c_fields)
				{
					std::cout << std::setw(colWidths[column]) << std::left << row.substr(start) << "|";
					column++;
				}
				for (; column < c_fields; ++column)
				{
					std::cout << std::setw(colWidths[column]) << "" << "|";
				}

				std::cout << std::endl;
			};

		size_t pos;
		while ((pos = op.find(delim)) != std::string::npos)
		{
			std::string record = op.substr(0, pos);
			PrintRow(record);
			op = op.substr(pos + 1);
		}
		if (!op.empty())
		{
			PrintRow(op);
		}

		std::cout << std::string(totalWidth, '-') << std::endl;
	}
	bool ShowAllMovies()
	{
		std::string resSet;
		if (Select::SelectMovie(resSet) == Error::ERROR_NOT_EXISTS) // get movies result set
		{
			Utils::ErrMsg("Movie does not exist");
			return false;
		}
		std::string fields[] = { "Name","Genre","Language","ReleaseYear" };

		int widthField[] = {20,20,20,10};
		Misc::PrintStrTok(resSet, '|', fields, 4,widthField);

		return true;
	}
	bool ShowAllShows(const std::string& movieName)
	{
		std::string shows;
		if (Select::SelectShow(movieName, shows) == Error::ERROR_NOT_EXISTS || shows.empty())
		{
			Utils::ErrMsg("No shows are found");
			return false;
		}
		std::string fields[] = { "ID","Date","Price" };

		int widthField[] = {5,20,10};
		Misc::PrintStrTok(shows, '|', fields, 3,widthField);
		return true;
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