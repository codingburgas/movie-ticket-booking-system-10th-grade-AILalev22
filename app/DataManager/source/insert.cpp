#include "pch.h"
#include "entity.h"
#include "insert.h"
#include "find.h"
#include "valid.h"
namespace Insert
{
	int InsertAccount(const Entity::Account& acc)
	{
		if (Find::FindAccount(acc)) return EXISTS;

		if (!Validation::IsValidAccount(acc)) return INVALID_INPUT;

		auto& shsql = Manager::GetSQL();
		if (!shsql->SetDB("dataticket"))
		{
			return ERROR_DATABASE;
		}

		std::string hemail, hpass;
		Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);
		
		if (shsql->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", hemail, hpass))
		{
			return SUCCESSFUL;
		}
		return ERROR_DATABASE;
	}
}