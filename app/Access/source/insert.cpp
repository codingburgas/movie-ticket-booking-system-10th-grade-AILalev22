#include "pch.h"
#include "insert.h"
namespace Insert
{
	int InsertAccount(const Entity::User& acc)
	{
		auto& shsql = MySQL::GetSQL();

		std::string hemail, hpass;
		Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);
		
		if (shsql->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", hemail, hpass))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_EXISTS;
	}
}