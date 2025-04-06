#include "pch.h"
#include "auth.h"
#include "valid.h"
#include "insert.h"
namespace Auth
{
	int SignUser(const Entity::User& acc)
	{
		if (Auth::LogUser(acc) == Error::ERROR_EXISTS) return Error::ERROR_EXISTS;
		if (!Validation::IsValidAccount(acc)) return Error::ERROR_INPUT;
		return Insert::InsertAccount(acc);
	}
	int LogUser(const Entity::User& acc)
	{
		auto shsql = MySQL::GetSQL();
		std::string row;
		std::string hemail;

		Crypt::CalcHash(acc.email, hemail);

		if (shsql->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + hemail + "'", row)) // possible injection, fix later Read
		{
			std::string hpass;
			Crypt::CalcHash(acc.password, hpass);
			row.pop_back();

			return row == hpass ? Error::SUCCESSFUL : Error::ERROR_INPUT;
		}
		return Error::ERROR_DATABASE;
	}
}