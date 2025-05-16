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
		// price
		float price;

		Show() : price(0) {}
	};
	// admin or customer data
    struct User
	{
		std::string email;
		std::string password;
	};
	// customer booking data
	struct Booking
	{
		int showId;
		// seat number
		int seat;
		// price with added seat tax
		double finalPrice;
		// booking status
		std::string status;

		Booking() : finalPrice(0),seat(0),showId(0) {}
	};
}
