#include "pch.h"
#include "register.h"
#include "find.h"
#include "valid.h"
#include "insert.h"
namespace Process
{
	int ProcessAccount(const Entity::User& acc)
	{
		if (Find::FindAccount(acc)) return Error::ERROR_EXISTS;
		if (!Validation::IsValidAccount(acc)) return Error::ERROR_INPUT;
		return Insert::InsertAccount(acc);
	}
}