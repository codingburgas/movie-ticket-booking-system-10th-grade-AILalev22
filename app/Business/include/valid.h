#pragma once

namespace Validation
{
	// return whether email follows a correct pattern or not
	bool IsValidEmail(const std::string& email);
	// return if pass contains nums,special chars, upper letters and no forbidden chars
	bool IsValidPass(const std::string& pass);
	// returns whether email and pass are valid
	bool IsValidAccount(const Entity::User& acc);
}