#pragma once
#include <unordered_map>

enum Error
{
	ERROR_INPUT,
	ERROR_DATABASE,
	ERROR_EXISTS,
	ERROR_NOT_EXISTS,
	ERROR_FAILED,
	SUCCESSFUL
};

enum Seat
{
	SILVER =1,
	GOLD,
	PLATINUM
};

extern std::unordered_map<Seat, int> seatPrice;
extern std::unordered_map<Seat, std::string> seatType;

/**
	 * @brief Signs up a new user account.
	 *
	 * @param acc Reference to a User entity to be registered.
	 * @return int Status code (e.g., 0 = success, other = error).
	 */
int SignUser(Entity::User& acc);

/**
 * @brief Logs in an existing user.
 *
 * @param acc Reference to a User entity attempting to log in.
 * @return int Status code (e.g., 0 = success, other = failure).
 */
int LogUser(Entity::User& acc);



