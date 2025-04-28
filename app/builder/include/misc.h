#pragma once

namespace Misc
{
	// enter a non negative number into a str
	void EnterNumber(std::string& num, bool floating = 0);
	// enter movie struct data
	void EnterMovieData(Entity::Movie& movie);
	//// enter movie cinema name
	//void EnterMovieCinema(Entity::Movie& movie);
	void EnterDateTime(std::string& date);
	// enter show struct data
	void EnterShowData(Entity::Show& show);
	// enter user's password securly
	void EnterUserPassword(Entity::User& user);
	// print string with delimeter in table format
	void PrintStrTok(std::string op, char delim,const std::string fields[], int c_fields);
}