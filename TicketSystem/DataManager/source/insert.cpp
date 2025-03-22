#include "pch.h"
#include "insert.h"
#include "crypt.hpp"
namespace Insert
{
	bool InsertAccount(const std::string& email, const std::string& pass)
	{
		CTOR* ctemp = Manager::GetSQL();
		if (!ctemp->SetDB("dataticket"))
		{
			return false;
		}

		std::string hemail, hpass;
		Crypt::CalcHash(email, hemail);
		Crypt::CalcHash(pass, hpass);
		if (ctemp->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", hemail, hpass))
		{
			return true;
		}
		return false;		
	}
}