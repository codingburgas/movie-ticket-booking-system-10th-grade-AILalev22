#pragma once

namespace Insert
{
	enum
	{
		EXISTS,
		INVALID_INPUT,
		ERROR_DATABASE,
		SUCCESSFUL
	};
	// insert an account into the database
	int InsertAccount(const Manager::Account& acc);
}