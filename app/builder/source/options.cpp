#include "pch.h"
#include "options.h"
#include "core\auth.h"
#include "menu.h"
#include "core\valid.h"
#include "core\crud.h"
#include "misc.h"
#include "core\smtp.h"
namespace Options
{	
	int LogSign(int mode)
	{	
		Entity::User user; // user data struct

		std::cout << "\nEnter email\n:";
		std::cin >> user.email;

		Misc::EnterUserPassword(user);

		int res = mode == 1 ? Auth::LogUser(user) : Auth::SignUser(user);
		if (res != Error::SUCCESSFUL) // if logging or signing is not successful
		{
			switch (res)
			{
			case Error::ERROR_NOT_EXISTS: Utils::ErrMsg("User does not exist"); break;
			case Error::ERROR_INPUT: mode == 1 ? Utils::ErrMsg("Invalid input") : Utils::ErrMsg("Email needs to follow this example:\n\"example@gmail.com\"\nPassword needs to contain:\n1 small letter\n1 big letter\n1 number", 5); break;
			case Error::ERROR_EXISTS: Utils::ErrMsg("User already exists"); break;
			default: Utils::ErrMsg("Unexpected error"); break;
			}
			return res;
		}
		conf.currUser = user; // assign current user data to config

		return stricmp(user.email.c_str(), conf.ademail.c_str()) == 0 ? Menu::ENTER_ADMIN : Menu::ENTER_CUSTOMER;
	}
	void InsertMovie()
	{
		Entity::Movie add;
		Misc::EnterMovieData(add);

		int res = Error::ERROR_FAILED;
		if (Validation::IsValidMovie(add))
		{
			std::string dstData;
			if (Select::SelectMovie(dstData,add.name) == Error::ERROR_NOT_EXISTS)
			{
				res = Insert::InsertMovie(add);
			}
			else
				res = ERROR_EXISTS;
		}
		else
		{
			Utils::ErrMsg("Incorrect movie data");
		}

		if (res == Error::ERROR_EXISTS)
		{
			Utils::ErrMsg("Movie already exists");
		}
		else if(res == Error::SUCCESSFUL)
		{
			Utils::ErrMsg("Movie has been added successfully");

			std::string msg =
				"A new movie has been released!\n\n"
				"Name: " + add.name + "\n"
				"Genre: " + add.genre + "\n"
				"Language: " + add.language + "\n"
				"Release year: " + std::to_string(add.releaseYear) + "\n";
			SMTP::NotifyUsers("New movie", msg); // notify all users of newly inserted movie
		}
	}
	void DeleteMovie()
	{
		Misc::ShowAllMovies();

		Entity::Movie add;
		std::cout << "\n\nEnter movie's name\n:";
		std::cin >> add.name;
		
		switch (Delete::DeleteMovie(add))
		{
		case Error::SUCCESSFUL: Utils::ErrMsg("Successfully deleted"); break;
		case Error::ERROR_FAILED: Utils::ErrMsg("Error! Movie cannot be deleted");; break;
		}
	}
	void InsertShow()
	{
		if(!Misc::ShowAllMovies()) return; // print movies so admin can see names
		std::cout << "\n\n";

		Entity::Show add;
		if (Misc::EnterShowData(add))
		{
			std::vector<Entity::Show> shows;
			if (Select::SelectShows(add.movieName, shows) == Error::SUCCESSFUL) // check if show exists before inserting
			{
				for (const auto& show : shows)
				{
					if (show.date == add.date && show.cinemaName == add.cinemaName)
					{
						Utils::ErrMsg("Show already exists");
						return;
					}
				}
			}
			switch (Insert::InsertShow(add))
			{
			case Error::SUCCESSFUL: Utils::ErrMsg("Successfully inserted"); break;
			case Error::ERROR_EXISTS: Utils::ErrMsg("Show already exists"); break;
			default: Utils::ErrMsg("Unexpected error. Try later"); break;
			}
		}
	}
	void DeleteShow()
	{
		Misc::ShowAllMovies();
		std::cout << "\n\nEnter movie's name\n:";
		std::string movieName;
		std::cin >> movieName;

		std::string dstData;
		if (!Select::SelectMovie(dstData,movieName))
		{
			Utils::ErrMsg("Movie does not exist"); // check if movie exists
			return;
		}

		Utils::Clear();
		if (!Misc::ShowAllShows(movieName))
		{
			return; // stop if now shows are available
		}

		std::cout << "Enter show's ID\n";
		std::string id;
		Misc::EnterNumber(id);
		
		switch (Delete::DeleteShow(id))
		{
		case Error::SUCCESSFUL: Utils::ErrMsg("Successfully deleted"); break;
		case Error::ERROR_FAILED: Utils::ErrMsg("Show not found"); break;
		}
	}
	void UpdateShow()
	{
		Misc::ShowAllMovies();

		std::cout << "\n\nEnter movie's name\n:";
		std::string movieName;
		std::cin >> movieName;
		
		Utils::Clear();
		if (!Misc::ShowAllShows(movieName)) // if no shows for entered movie, stop func
		{
			return;
		}
		
		std::cout << "\nEnter show's ID\n";
		std::string id;
		Misc::EnterNumber(id);
		
		Entity::Show newShow;
		newShow.movieName = movieName; //assign entered movie name

		std::cout << "Enter show's new date in YYYY-MM-DD HH:MM:SS format\n";
		Misc::EnterDateTime(newShow.date);
		Utils::Clear();

		std::cout << "Enter show's new price\n";
		std::string price;
		Misc::EnterNumber(price, true);
		newShow.price = std::stof(price);

		Utils::Clear();
		Misc::EnterShowCinema(newShow);

		Update::UpdateShow(id, newShow) ? Utils::ErrMsg("Successfully updated") : Utils::ErrMsg("Update failed");
	}
	void BookMovie()
	{
		Entity::Show chosenShow;
		if (!Misc::ChooseMovieShow(chosenShow))
		{
			return;
		}

		Entity::Booking book;
		book.showId = chosenShow.id;
		book.userId = conf.currUser.id;

		Misc::EnterBookingData(book,chosenShow);
	}
	void CancelBooking()
	{
		if (!Misc::ShowBookings()) return;
		
		std::string x, y;
		std::cout << "\n\nEnter seat row:\n";
		Misc::EnterNumber(x);

		Misc::ShowBookings();

		std::cout << "\n\nEnter seat column:\n";
		Misc::EnterNumber(y);

		POINT p = { std::stod(x),std::stod(y) }; // seat row and col of booking to delete

		if (Delete::DeleteBooking(p) == Error::SUCCESSFUL)
		{
			Utils::ErrMsg("Canceled successfully");
			std::string msg =
				"You have canceled a booking\n"
				"Seat column: " + x + "\n"
				"Seat row: " + y + "\n";
			SMTP::NotifyUsers("Booking cancel", msg, { conf.currUser.email });
		}
		else
		{
			Utils::ErrMsg("Internal error, please try again later");
		}
	}
}
