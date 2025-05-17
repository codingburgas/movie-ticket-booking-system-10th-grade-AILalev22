#pragma once

namespace Auth
{
	// sign in user
	int SignUser(Entity::User& acc);
	// log in user
	int LogUser(Entity::User& acc);
	// returns insert crud query result if valid
	// if not valid returns error_input
}