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



