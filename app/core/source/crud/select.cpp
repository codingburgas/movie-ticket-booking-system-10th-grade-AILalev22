#include "pch.h"

namespace Select
{
	int SelectUserExist(Entity::User& acc)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		std::string hpass; // hashed password
		//Crypt::CalcHash(acc.email, hemail); // hash email and pass values
		Crypt::CalcHash(acc.password, hpass);

		std::string retrievedPass;
		if (shsqlInst->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", retrievedPass)) // possible injection, fix later Read
		{
			retrievedPass.pop_back(); // remove last pipe appended from Read fn

			Utils::DbgMsg("SelectUserExist() : %s %s", acc.email.c_str(), retrievedPass.c_str());

			if (retrievedPass == hpass)
			{
				std::string idDst;
				if (shsqlInst->Read("%d", "SELECT ID FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", idDst))
				{
					try
					{
						acc.id = std::stod(idDst);

						Utils::DbgMsg("SelectUserExist() : %d", acc.id);
					}
					catch (...)
					{
						Utils::DbgMsg("error SelectUserExist() id cannot read");
					}
				}
				return Error::SUCCESSFUL;
			}
			return Error::ERROR_INPUT; // if email is found but password is wrong, return error_input
		}
		return Error::ERROR_NOT_EXISTS; // if email isn't found return error_not_exist
	}

	int SelectAllUsersEmail(std::vector<std::string>& vec)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string dst;

		if (shsqlInst->Read("%s", "SELECT EMAIL FROM ACCOUNTS WHERE ID > 1 ORDER BY ID ASC", dst)) // fix later add WHERE ID>=1 for admin
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

			for(const auto& email : vec)
			Utils::DbgMsg("SelectAllUsersEmail() : %s", email.c_str());

			if (!vec.empty())
				return Error::SUCCESSFUL;
		}
		return Error::ERROR_FAILED;
	}

	int SelectMovie(std::string& dst, const std::string& name)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		if (shsqlInst->Read("%s %s %s %d", name.empty() ? "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES" : "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES WHERE NAME = '" + name + '\'', dst))
		{
			Utils::DbgMsg("SelectMovie() : %s", dst.c_str());

			if(!dst.empty())
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_NOT_EXISTS;
	}

	int SelectShow(const std::string& movieName,std::string& dst)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		if (shsqlInst->Read("%d %s %f %s", "SELECT ID,DATE,PRICE,CINEMANAME FROM SHOWS WHERE MOVIENAME = '" + movieName + "'", dst))
		{
			Utils::DbgMsg("SelectShow() : %s", dst.c_str());

			if(!dst.empty())
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_NOT_EXISTS;
	}
}