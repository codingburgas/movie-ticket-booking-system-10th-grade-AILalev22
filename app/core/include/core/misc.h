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
	SILVER,
	GOLD,
	PLATINUM
};

enum Notification
{
	NEW_MOVIE, 
	BOOKING_CONFIRMED, 
	BOOKING_CANCELED
};

enum BookingStatus
{
	PENDING,
	CONFIRMED,
	CANCELED
};



