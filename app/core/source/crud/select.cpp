#include "pch.h"

namespace Select
{
	int SelectUser(const Entity::User& acc)
	{
		auto shsql = Manager::GetSQL();

		std::string hpass; // hashed password
		//Crypt::CalcHash(acc.email, hemail); // hash email and pass values
		Crypt::CalcHash(acc.password, hpass);

		std::string retrievedPass;
		if (shsql->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", retrievedPass)) // possible injection, fix later Read
		{
			retrievedPass.pop_back(); // remove last pipe appended from Read fn
			return retrievedPass == hpass ? Error::SUCCESSFUL : Error::ERROR_INPUT; // if email is found but password is wrong, return error_input
		}
		return Error::ERROR_NOT_EXISTS; // if email isn't found return error_not_exist
	}
	int SelectAllUsersEmail(std::vector<std::string>& vec)
	{
		auto shsql = Manager::GetSQL();
		std::string dst;

		if (shsql->Read("%s", "SELECT EMAIL FROM ACCOUNTS ORDER BY ID ASC", dst)) // fix later add WHERE ID>=1 for admin
		{
			size_t from = 0,to;

			while ((to = dst.find('|', from)) != std::string::npos)
			{
				std::string email = dst.substr(from, to - from);
				if (!email.empty())
					vec.push_back(email);

				from = to + 1;
			}

			std::string last = dst.substr(from);
			if (!last.empty())
				vec.push_back(last);

			if (!vec.empty())
				return Error::SUCCESSFUL;
		}
		return Error::ERROR_FAILED;
	}
	int SelectMovie(std::string& dst, const std::string& name)
	{
		auto shsql = Manager::GetSQL();

		if (shsql->Read("%s %s %s %d", name.empty() ? "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES" : "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES WHERE NAME = '" + name + '\'', dst))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_NOT_EXISTS;
	}
}