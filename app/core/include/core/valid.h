#pragma once

namespace Validation
{
	// returns whether email and pass are valid
	bool IsValidUser(const Entity::User& acc);
	// returns whether movie is valid or not
	bool IsValidMovie(const Entity::Movie& movie);
	// return whether a show is valid
	bool IsValidShow(const Entity::Show& show);
}