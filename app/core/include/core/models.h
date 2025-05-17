#pragma once
#include <string>
namespace Entity
{
	// movie data
	struct Movie
	{
		// main info
		std::string name;
		std::string genre;
		int releaseYear;
		std::string language;

		Movie() : releaseYear(1888) {}
	};
	// movie display data
	struct Show
	{
		// movie name
		std::string movieName;
		// date in YYYY-MM-DD HH:MM:SS format
		std::string date;
		float price;

		std::string cinemaName;

		Show() : price(0) {}
	};
	// user data
    struct User
	{
		std::string email;
		std::string password;
		int id;
	};
	// customer booking data
	struct Booking
	{
		int showId;
		// seat row
		int seatX;
		// seat column
		int seatY;
		// price with added seat tax
		float finalPrice;
		// booking status
		std::string status;

		int hallNumber;
		Booking() : finalPrice(0),seatX(0),seatY(0),showId(0),hallNumber(0) {}
	};
}
