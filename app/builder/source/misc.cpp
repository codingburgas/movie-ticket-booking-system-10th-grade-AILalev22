#include "pch.h"
#include "misc.h"
#include <regex>
#include <conio.h>
#include <iomanip>
#include "main.h"
#include "core\crud.h"
#include "core\matrix.h"
namespace Misc
{
	void EnterNumber(std::string& num, bool floating)
	{
		int cdot = 0; // floating point count
		for (;;)
		{
			cdot = 0;
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
		if (Select::SelectMovie(dstData,show.movieName) == Error::ERROR_NOT_EXISTS)
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

		EnterShowCinema(show);

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

		int widthField[] = {20,20,20,15};
		Misc::PrintStrTok(resSet, '|', fields, 4,widthField);

		return true;
	}
	bool ShowAllShows(const std::string& movieName)
	{
		std::string dst;
		if (Select::SelectShows(movieName, dst) == Error::ERROR_NOT_EXISTS || dst.empty())
		{
			Utils::ErrMsg("No shows are found");
			return false;
		}
		std::string fields[] = { "ID","Date","Price","CinemaName"};

		int widthField[] = {5,20,10,15};
		Misc::PrintStrTok(dst, '|', fields, 4,widthField);
		return true;
	}
	void ShowBookings()
	{
		std::string dstBookings;
		if (Select::SelectBookings(dstBookings, conf.currUser.id) == Error::ERROR_NOT_EXISTS)
		{
			Utils::ErrMsg("No available bookings");
		}
		//SHOWID,FINALPRICE,SEATX,SEATY,SEATTYPE,HALLNUMBER
		std::string fields[] = { "ShowId","Price","Seat row","Seat column","Seat type","Hall number" };
		int widthField[] = { 10,10,10,10,10,10 };
		Misc::PrintStrTok(dstBookings, '|', fields, 6, widthField);

	}
	bool ChooseMovieShow(Entity::Show& show)
	{
		if(!Misc::ShowAllMovies()) return false;
		std::cout << "\n\nEnter movie's name to book\n:";
		std::string movieName;
		std::cin >> movieName;

		Utils::Clear();
		if (!Misc::ShowAllShows(movieName)) return false;

		std::cout << "Enter show's id to book:\n";
		std::string choice;// id of chosen show
		Misc::EnterNumber(choice);

		show.id = std::stod(choice);
		Utils::Clear();
		
		return Select::SelectShow(show.id, show) == Error::SUCCESSFUL;
	}
	int EnterSeat(const std::vector<Entity::Booking>& lsBookings, Entity::Booking& book);

	void EnterBookingData(Entity::Booking& book,const Entity::Show& show)
	{
		std::cout << "Enter seat type number:\n1. Silver\n2. Gold\n3. Platinum\n";
		std::string choice;
		do
		{
			std::cout << ":";
			std::cin >> choice;
		} while (choice != "1" && choice != "2" && choice != "3");
		book.seatType = seatType.at((Seat)(std::stod(choice))); //assign seat type

		Utils::Clear();

		book.finalPrice = show.price + seatPrice.at((Seat)std::stod(choice)); //final price with added seat price

		Utils::Clear();

		std::string hallNumber;
		do
		{
			std::cout << "Enter hall number:\n1. Hall 1\n2. Hall 2\n3. Hall 3\n4. Hall 4\n";
			Misc::EnterNumber(hallNumber);
		} while (std::stod(hallNumber) > HALLS);
		book.hallNumber = std::stod(hallNumber);
		
		std::vector<Entity::Booking> bookings;
		if (Select::SelectBookings(bookings, show.id,std::stod(hallNumber)) != Error::ERROR_FAILED)
		{
			int seatNum = EnterSeat(bookings,book);
			
			if (Insert::InsertBooking(book) == Error::SUCCESSFUL)
			{
				Utils::ErrMsg("Show booked successfuly");
				std::string msg =
					"You have made a booking\n"
					"Price: " + std::to_string(book.finalPrice).substr(0,4) + "\n"
					"Hall: " + std::to_string(book.hallNumber) + "\n"
					"Seat type: " + book.seatType + "\n"
					"Seat row: " + std::to_string(book.seatX) + "\n"
					"Seat column: " + std::to_string(book.seatY) + "\n"
					"Seat number: " + std::to_string(seatNum) + "\n"
					"Show ID: " + std::to_string(book.showId) + "\n";

				SMTP::NotifyUsers("New booking", msg, { conf.currUser.email });
			}
			else
				Utils::ErrMsg("Unexpected error. Please try again later");
		}
		else
		{
			Utils::ErrMsg("Unexpected error. Please try again later");
		}
	}

	int EnterSeat(const std::vector<Entity::Booking>& lsBookings,Entity::Booking& book)
	{
		Matrix::Sparse seats(COL_SIZE, ROW_SIZE, "x"); //seats in hall
		int nSeat = 1;

		for (int i = 0; i < ROW_SIZE; i++) // set all seats initialy to numeric values
		{
			for (int j = 0; j < COL_SIZE; j++)
			{
				seats.Set(i, j, std::to_string(nSeat));
				nSeat++;
			}
		}
		for (const auto& book : lsBookings) //mark booked seats at chosen hall as x
		{
			seats.Set(book.seatX, book.seatY, "x");
		}

		for (;;)
		{
			std::string seatVal;
			do
			{	
				std::cout << "\nSeats seen as 'x' are booked\n\n";
				seats.Print();

				std::cout << "Enter seat number:\n";
				Misc::EnterNumber(seatVal);
			} while (std::stod(seatVal) > ROW_SIZE * COL_SIZE);

			POINT p = { DEFAULT_POINT,DEFAULT_POINT }; //default pos
			POINT p2 = seats.Get(seatVal); // entered seat pos
			if (p2.x == p.x && p2.y == p.y)
			{
				Utils::ErrMsg("Seat is booked, try again");
			}
			else
			{			
				book.seatX = p2.x;
				book.seatY = p2.y;
				return std::stod(seatVal);
			}
		}	
	}
	void EnterShowCinema(Entity::Show& show)
	{
		std::cout << "Choose show's cinema:\n1. CinemaBurgas\n2. CinemaVarna\n";
		std::string choice;
		do
		{
			std::cout << ':';
			std::cin >> choice;
		} while (choice != "1" && choice != "2");

		show.cinemaName = choice == "1" ? "CinemaBurgas" : "CinemaVarna";
		Utils::Clear();
	}
}