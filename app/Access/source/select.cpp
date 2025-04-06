#include "pch.h"
#include "select.h"

namespace Select
{
	int SelectUser(const Entity::User& acc)
	{
		auto shsql = MySQL::GetSQL();

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
}