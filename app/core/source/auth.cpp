#include "pch.h"
#include "auth.h"
#include "valid.h"
#include "crud.h"
namespace Auth
{
	int SignUser(const Entity::User& acc)
	{
		if (Auth::LogUser(acc) != Error::ERROR_NOT_EXISTS) return Error::ERROR_EXISTS;
		if (!Validation::IsValidUser(acc)) return Error::ERROR_INPUT;
		return Insert::InsertUser(acc);
	}
	int LogUser(const Entity::User& acc)
	{
		return Select::SelectUser(acc); // return select db operation result
	}
}