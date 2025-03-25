#include "pch.h"
#include "find.h"
namespace Find
{
	bool FindAccount(const Entity::User& acc)
	{
		auto shsql = MySQL::GetSQL();
		std::string row;
		std::string hemail;

		Crypt::CalcHash(acc.email, hemail);

		if (shsql->Read("%s", "SELECT EMAIL FROM ACCOUNTS WHERE EMAIL = '" + hemail + "'", row)) // possible injection, fix later Read
		{
			return !row.empty();
		}		
		return false;
	}
}
