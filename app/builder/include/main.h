#pragma once

#include "release.h"
#include "core\type.h"

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
	std::string ademail;

	// main database schema in mysql server
	std::string schema;

	// app smtp sender user
	Entity::User sender;
	// app smtp server
	std::string smtpServer;

};
extern Config conf; // global app config

bool LoadConfig(Config& conf);
