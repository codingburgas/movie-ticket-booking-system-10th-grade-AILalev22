#include "pch.h"

namespace Select
{
	int SelectUser(const Entity::User& acc)
	{
		auto shsql = Manager::GetSQL();

		std::string hemail, hpass;
		Crypt::CalcHash(acc.email, hemail); // hash email and pass values
		Crypt::CalcHash(acc.password, hpass);

		std::string retrieved_pass;
		if (shsql->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + hemail + "'", retrieved_pass)) // possible injection, fix later Read
		{
			retrieved_pass.pop_back(); // remove last pipe appended from Read fn
			return retrieved_pass == hpass ? Error::SUCCESSFUL : Error::ERROR_INPUT; // if email is found but password is wrong, return error_input
		}
		return Error::ERROR_NOT_EXISTS; // if email isn't found return error_not_exist
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