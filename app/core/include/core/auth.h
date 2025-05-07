#pragma once

namespace Auth
{
	// sign in user
	int SignUser(const Entity::User& acc);
	// log in user
	int LogUser(const Entity::User& acc);
	// returns insert crud query result if valid
	// if not valid returns error_input
}