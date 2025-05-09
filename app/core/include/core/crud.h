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
}
namespace Select
{
	// select a user from db
	int SelectUser(const Entity::User& acc); 
	// select all users' emails from db
	int SelectAllUsersEmail(std::vector<std::string>& vec);
	// get movie data by name
	// if no name is passed, all movies are retrieved
	int SelectMovie(std::string& dst, const std::string& name = "");
}
namespace Delete
{
	// delete a movie from the database
	// returns successful if successfully deleted
	// returns error_not_exists if query fails
	int DeleteMovie(const Entity::Movie& movie);
	int DeleteShow(const Entity::Show& show);
}
namespace Update
{
	// update a show found by datetime
	bool UpdateShow(const std::string& oldDate, const Entity::Show& show);
}