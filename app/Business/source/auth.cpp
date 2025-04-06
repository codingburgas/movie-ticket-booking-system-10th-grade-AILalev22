#include "pch.h"
#include "auth.h"
#include "valid.h"
#include "insert.h"
#include "select.h"
namespace Auth
{
	int SignUser(const Entity::User& acc)
	{
		if (Auth::LogUser(acc) != Error::ERROR_NOT_EXISTS) return Error::ERROR_EXISTS;
		if (!Validation::IsValidAccount(acc)) return Error::ERROR_INPUT;
		return Insert::InsertAccount(acc);
	}
	int LogUser(const Entity::User& acc)
	{
		return Select::SelectUser(acc); // return select db operation result
	}
}