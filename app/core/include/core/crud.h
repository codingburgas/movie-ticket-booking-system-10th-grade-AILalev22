#pragma once

namespace Insert
{
	// insert an account into the database
	int InsertUser(const Entity::User& acc);
	// insert a movie into the database
	// returns successful if query succeeds
	// return error_exists if query fails
	int InsertMovie(const Entity::Movie& movie);
	int InsertShow(const Entity::Show& show);
	// insert customer booking entity
	// return successful if inserted correctly
	// returns error_exists if write fails
	int InsertBooking(const Entity::Booking& book);
}
namespace Select
{
	// check if a user exists
	// returns successful if exist
	// returns error_input if password is wrong only
	// returns errror_not_exist if email and password are not found
	// puts id into user struct
	int SelectUserExist(Entity::User& acc);
	// select all users' emails from db
	int SelectAllUsersEmail(std::vector<std::string>& vec);
	// get movie data by name
	// if no name is passed, all movies are retrieved
	int SelectMovie(std::string& dst, const std::string& name = "");
	// get all shows of a certain movie in vector
	int SelectShows(const std::string& movieName, std::vector<Entity::Show>& shows);
	// get all shows of a certain movie in Read dst format
	int SelectShows(const std::string& movieName, std::string& dst);
	// select show by id
	int SelectShow(const int& id, Entity::Show& show);
	// select bookings based on showId or hallNumber
	// if showId or hallNumber are bigger than one they're used in WHERE clause
	int SelectBookings(std::vector<Entity::Booking>& bookings, int showId,int hallNumber);
	// select user bookings based on user id
	// res set is returned in string
	int SelectBookings(std::string& dst, int userId);
}
namespace Delete
{
	// delete a movie from the database
	// returns successful if successfully deleted
	// returns error_not_exists if query fails
	//returns error_exists if movie has shows
	int DeleteMovie(const Entity::Movie& movie);
	int DeleteShow(const std::string& idShow);
	// delete booking based on row and col coords
	int DeleteBooking(const POINT& coord);
}
namespace Update
{
	// update a show found by id
	bool UpdateShow(const std::string& idShow, const Entity::Show& show);
}