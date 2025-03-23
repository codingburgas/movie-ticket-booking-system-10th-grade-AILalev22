#include "pch.h"
#include "find.h"
#include "crypt.h"
namespace Find
{
	bool FindAccount(const Manager::Account& acc)
	{
		auto shsql = Manager::GetSQL();
		if (!shsql->SetDB("dataticket"))
		{
			return false;
		}

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
