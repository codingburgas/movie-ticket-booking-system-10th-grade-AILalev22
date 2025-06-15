#pragma once

namespace Insert
{
	/**
	 * @brief Inserts a user account into the database.
	 *
	 * @param acc The User entity to insert.
	 * @return int Status code.
	 */
	int InsertUser(const Entity::User& acc);

	/**
	 * @brief Inserts a movie into the database.
	 *
	 * @param movie The Movie entity to insert.
	 * @return int Returns `successful` if query succeeds, `error_exists` if it fails.
	 */
	int InsertMovie(const Entity::Movie& movie);

	/**
	 * @brief Inserts a show into the database.
	 *
	 * @param show The Show entity to insert.
	 * @return int Status code.
	 */
	int InsertShow(const Entity::Show& show);

	/**
	 * @brief Inserts a customer booking entity.
	 *
	 * @param book The Booking entity to insert.
	 * @return int Returns `successful` if inserted correctly, `error_exists` if write fails.
	 */
	int InsertBooking(const Entity::Booking& book);
}

namespace Select
{
	/**
	 * @brief Checks if a user exists in the database.
	 *
	 * @param acc The User entity with email and password.
	 * @return int `successful` if user exists, `error_input` if password is wrong,
	 * `error_not_exist` if both email and password are not found. User ID is stored in acc.id.
	 */
	int SelectUserExist(Entity::User& acc);

	/**
	 * @brief Retrieves all user emails from the database.
	 *
	 * @param vec Vector to store user emails.
	 * @return int Status code.
	 */
	int SelectAllUsersEmail(std::vector<std::string>& vec);

	/**
	 * @brief Retrieves movie data by name.
	 *
	 * @param dst String to store the result.
	 * @param name Optional movie name. If empty, retrieves all movies.
	 * @return int Status code.
	 */
	int SelectMovie(std::string& dst, const std::string& name = "");

	/**
	 * @brief Retrieves all shows for a given movie name into a vector.
	 *
	 * @param movieName The name of the movie.
	 * @param shows Vector to store resulting shows.
	 * @return int Status code.
	 */
	int SelectShows(const std::string& movieName, std::vector<Entity::Show>& shows);

	/**
	 * @brief Retrieves all shows for a given movie name into a string.
	 *
	 * @param movieName The name of the movie.
	 * @param dst String to store formatted results.
	 * @return int Status code.
	 */
	int SelectShows(const std::string& movieName, std::string& dst);

	/**
	 * @brief Retrieves a show by its ID.
	 *
	 * @param id The show ID.
	 * @param show Reference to store the result.
	 * @return int Status code.
	 */
	int SelectShow(const int& id, Entity::Show& show);

	/**
	 * @brief Retrieves bookings based on show ID or hall number.
	 *
	 * @param bookings Vector to store bookings.
	 * @param showId Optional filter. Used if > 0.
	 * @param hallNumber Optional filter. Used if > 0.
	 * @return int Status code.
	 */
	int SelectBookings(std::vector<Entity::Booking>& bookings, int showId, int hallNumber);

	/**
	 * @brief Retrieves bookings for a given user ID in a string format.
	 *
	 * @param dst String to store formatted bookings.
	 * @param userId ID of the user.
	 * @return int Status code.
	 */
	int SelectBookings(std::string& dst, int userId);
}

namespace Delete
{
	/**
	 * @brief Deletes a movie from the database.
	 *
	 * @param movie The Movie entity to delete.
	 * @return int Returns `successful` if deleted, `error_not_exists` if not found,
	 * `error_exists` if movie has related shows.
	 */
	int DeleteMovie(const Entity::Movie& movie);

	/**
	 * @brief Deletes a show from the database.
	 *
	 * @param idShow The ID of the show to delete.
	 * @return int Status code.
	 */
	int DeleteShow(const std::string& idShow);

	/**
	 * @brief Deletes a booking based on seat coordinates.
	 *
	 * @param coord The seat coordinates (row and column).
	 * @return int Status code.
	 */
	int DeleteBooking(const POINT& coord);
}

namespace Update
{
	/**
	 * @brief Updates a show using its ID.
	 *
	 * @param idShow The ID of the show to update.
	 * @param show Updated show data.
	 * @return true If update succeeded.
	 * @return false If update failed.
	 */
	bool UpdateShow(const std::string& idShow, const Entity::Show& show);
}