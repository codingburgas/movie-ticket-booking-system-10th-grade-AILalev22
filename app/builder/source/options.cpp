#include "pch.h"
#include "options.h"
#include "core\auth.h"
#include "menu.h"
#include "core\valid.h"
#include "core\crud.h"
#include "misc.h"
namespace Options
{	
	int LogSign(int mode, const std::string& adminEmail)
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
			case Error::ERROR_INPUT: Utils::ErrMsg(mode == 1 ? "Invalid input!" : "Email needs to follow this example:\n\"example@gmail.com\"\nPassword needs to contain:\n1 small letter\n1 big letter\n1 number",2); break;
			case Error::ERROR_EXISTS: Utils::ErrMsg("User already exists"); break;
			default: Utils::ErrMsg("Unexpected error"); break;
			}
			return res;
		}
		return user.email == adminEmail ? Menu::ENTER_ADMIN : Menu::ENTER_CUSTOMER;
	}
	void InsertMovie()
	{
		Entity::Movie add;
		Misc::EnterMovieData(add);

		int res;
		if (Validation::IsValidMovie(add))
		{
			res = Insert::InsertMovie(add);
		}
		else
		{
			Utils::ErrMsg("Incorrect movie data");
		}
		if (res == Error::ERROR_EXISTS)
		{
			Utils::ErrMsg("Movie already exists");
		}
	}
	void DeleteMovie()
	{
		Entity::Movie add;
		std::cout << "Enter name\n:";
		std::cin >> add.name;

		Delete::DeleteMovie(add) == Error::SUCCESSFUL ? Utils::ErrMsg("Successfully deleted") : Utils::ErrMsg("Movie not found");
	}
	void InsertShow()
	{
		Entity::Show add;
		Misc::EnterShowData(add);

		Insert::InsertShow(add) == Error::SUCCESSFUL ? Utils::ErrMsg("Successfully inserted") : Utils::ErrMsg("Show already exists");
	}
	void DeleteShow()
	{
		Entity::Show add;
		std::cout << "Enter show's date in YYYY-MM-DD HH:MM:SS\n";
		Misc::EnterDateTime(add.date);
		
		Delete::DeleteShow(add) == Error::SUCCESSFUL ? Utils::ErrMsg("Successfully deleted") : Utils::ErrMsg("Show not found");
	}
	void UpdateShow()
	{
		std::cout << "Enter show's old date\n";
		std::string oldDate;
		Misc::EnterDateTime(oldDate);
		
		std::cout << "Enter new show's data\n";
		Entity::Show newShow;
		Misc::EnterShowData(newShow);

		Update::UpdateShow(oldDate, newShow) ? Utils::ErrMsg("Successfully updated") : Utils::ErrMsg("Update failed");
	}
}