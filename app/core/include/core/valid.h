#pragma once
namespace Validation
{
	/// @brief Checks if the user's email and password are valid.
	/// @param acc User account to validate.
	/// @return true if valid, false otherwise.
	bool IsValidUser(const Entity::User& acc);

	/// @brief Checks if the movie data is valid.
	/// @param movie Movie entity to validate.
	/// @return true if valid, false otherwise.
	bool IsValidMovie(const Entity::Movie& movie);

	/// @brief Checks if the show data is valid.
	/// @param show Show entity to validate.
	/// @return true if valid, false otherwise.
	bool IsValidShow(const Entity::Show& show);

	/// @brief Checks if the SMTP server address is valid.
	/// @param addr SMTP address string.
	/// @return true if valid, false otherwise.
	bool IsValidSmtp(const std::string& addr);

	/// @brief Validates a credit card number using the Luhn algorithm.
	/// @param number Credit card number as a string.
	/// @return true if the number passes the Luhn check, false otherwise.
	bool LuhnCheck(const std::string& number);
}