#include "pch.h"
#include "insert.h"
#include "crypt.h"
#include "valid.h"
namespace Insert
{
	bool InsertAccount(const Manager::Account& acc)
	{
		if (!Validation::IsValidAccount(acc)) return false;

		auto shsql = Manager::GetSQL();
		if (!shsql->SetDB("dataticket"))
		{
			return false;
		}

		std::string hemail, hpass;
		Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);
		if (shsql->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", hemail, hpass))
		{
			return true;
		}
		return false;		
	}
}