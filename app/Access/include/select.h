#pragma once

namespace Select
{
	// search for hashed data in the db
	int SelectUser(const Entity::User& data);
}