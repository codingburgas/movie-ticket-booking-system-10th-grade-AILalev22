#include "pch.h"
#include "select.h"

namespace Select
{
	int SelectUser(const Entity::User& acc)
	{
		auto shsql = MySQL::GetSQL();

		std::string retrieved_pass;
		if (shsql->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", retrieved_pass)) // possible injection, fix later Read
		{
			return retrieved_pass == acc.password ? Error::ERROR_EXISTS : Error::ERROR_INPUT; // if email is found but password is wrong, return error_input
		}
		return Error::ERROR_NOT_EXISTS; // if email isn't found return error_not_exist
	}
}