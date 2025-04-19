#pragma once

namespace Validation
{
	// returns whether email and pass are valid
	bool IsValidUser(const Entity::User& acc);
}