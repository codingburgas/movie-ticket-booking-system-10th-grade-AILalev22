#pragma once

#include "config.h"
#include "core\type.h"

// allow unsafe c-style functions
#pragma warning(disable : 4996)
struct Config
{
	// halls count in each cinema
	uint halls;
	// cinema count
	uint cinemas;
	// rows with seats in each cinema
	uint rows;
	// cols with seats in each cinema
	uint cols;

	// db credentials
	std::string dbuser;
	std::string dbpass;
	std::string dbhost;
	// app admin username
	std::string aduser;

	// main database name in mysql server
	std::string dbname;

	Config() : halls(HALLS), cinemas(CINEMAS), rows(ROW_SIZE), cols(COL_SIZE),aduser(DB_ADMIN_USER),dbname(DB_NAME)
	{
		dbuser = getenv(DB_USER_ENV);
		dbpass = getenv(DB_PASS_ENV);
		dbhost = getenv(DB_HOST_ENV);
	}
};