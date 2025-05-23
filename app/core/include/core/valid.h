#pragma once

namespace Validation
{
	// returns whether email and pass are valid
	bool IsValidUser(const Entity::User& acc);
	// returns whether movie is valid or not
	bool IsValidMovie(const Entity::Movie& movie);
	// return whether a show is valid
	bool IsValidShow(const Entity::Show& show);
	// return whether smtp address is valid
	bool IsValidSmtp(const std::string& addr);
	// return whether credit card number is valid
	bool LuhnCheck(const std::string& number);
}