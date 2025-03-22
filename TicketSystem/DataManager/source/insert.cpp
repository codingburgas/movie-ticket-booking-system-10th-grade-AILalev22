#include "pch.h"
#include "insert.h"
#include "crypt.hpp"
#include "valid.h"
namespace Insert
{
	bool InsertAccount(const std::string& email, const std::string& pass)
	{
		if (!Validation::IsValidEmail(email) || !Validation::IsValidPass(pass)) return false;

		auto shsql = Manager::GetSQL();
		if (!shsql->SetDB("dataticket"))
		{
			return false;
		}

		std::string hemail, hpass;
		Crypt::CalcHash(email, hemail);
		Crypt::CalcHash(pass, hpass);
		if (shsql->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", hemail, hpass))
		{
			return true;
		}
		return false;		
	}
}