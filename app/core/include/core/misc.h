#pragma once

namespace Error
{
	enum
	{
		ERROR_INPUT,
		ERROR_DATABASE,
		ERROR_EXISTS,
		ERROR_NOT_EXISTS,
		ERROR_FAILED,
		SUCCESSFUL
	};
}
namespace Seat
{
	enum
	{
		SILVER,
		GOLD,
		PLATINUM
	};
}
namespace Notification
{
	enum
	{
		NEW_MOVIE, 
		BOOKING_CONFIRMED, 
		BOOKING_CANCELED
	};
}
namespace BookingStatus
{
	enum
	{
		PENDING,
		CONFIRMED,
		CANCELED
	};
}