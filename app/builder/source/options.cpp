#include "pch.h"
#include "options.h"
#include "bll\auth.h"
#include "menu.h"
namespace Options
{
	bool LogSign(int mode)
	{	
		Entity::User user; // user data struct

		std::cout << "\nEnter email\n:";
		std::cin >> user.email;

		std::cout << "\nEnter password\n:";
		std::cin >> user.password;

		int res = mode == 1 ? Auth::LogUser(user) : Auth::SignUser(user);
		if (res != Error::SUCCESSFUL)
		{
			switch (res)
			{
			case Error::ERROR_NOT_EXISTS: Utils::ErrMsg("User does not exist"); break;
			case Error::ERROR_INPUT: Utils::ErrMsg(mode == 1 ? "Invalid input!" : "Email needs to follow this example:\n\"example@gmail.com\"\nPassword needs to contain:\n1 small letter\n1 big letter\n1 number",2); break;
			case Error::ERROR_EXISTS: Utils::ErrMsg("User already exists"); break;
			default: Utils::ErrMsg("Unexpected error"); break;
			}
			return false;
		}
		return true;
	}
}