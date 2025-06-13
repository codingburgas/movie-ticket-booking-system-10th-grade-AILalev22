#pragma once
#include <string>

namespace Entity
{
	/// @brief Represents movie main information.
	struct Movie
	{
		std::string name;       ///< Movie name.
		std::string genre;      ///< Movie genre.
		int releaseYear;        ///< Year the movie was released.
		std::string language;   ///< Language of the movie.

		/// @brief Default constructor initializing releaseYear to 1888.
		Movie() : releaseYear(1888) {}
	};

	/// @brief Represents a movie show/display data.
	struct Show
	{
		std::string movieName;  ///< Name of the movie.
		std::string date;       ///< Show date and time in "YYYY-MM-DD HH:MM:SS" format.
		float price;            ///< Ticket price.

		std::string cinemaName; ///< Cinema name where the show takes place.

		int id;                 ///< Show identifier.

		/// @brief Default constructor initializing price to 0.
		Show() : price(0) {}
	};

	/// @brief Represents a user account.
	struct User
	{
		std::string email;      ///< User email address.
		std::string password;   ///< User password.
		int id;                 ///< User identifier.
	};

	/// @brief Represents a customer booking.
	struct Booking
	{
		int showId;             ///< Associated show identifier.
		int userId;             ///< Associated user identifier.

		int seatX;              ///< Seat row coordinate.
		int seatY;              ///< Seat column coordinate.

		float finalPrice;       ///< Price with seat tax included.

		int hallNumber;         ///< Hall number where the booking is made.

		std::string seatType;   ///< Type of seat booked.

		/// @brief Default constructor initializing numeric members to zero.
		Booking() : finalPrice(0), seatX(0), seatY(0), showId(0), hallNumber(0) {}
	};
}
