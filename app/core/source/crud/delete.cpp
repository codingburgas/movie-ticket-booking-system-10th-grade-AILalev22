#include "pch.h"

namespace Delete
{
	int Delete(const std::string& fmt, const std::string& querySelect,const std::string& queryDelete, bool checkDstEmpty = false)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string dstRead;
		
		if (shsqlInst->Read(fmt, querySelect, dstRead)) // select query to check if data exists because delete from always executes
		{
			if (checkDstEmpty && dstRead.empty()) return Error::ERROR_FAILED;

 			if (shsqlInst->Query(queryDelete))
			{
				return Error::SUCCESSFUL;
			}
		}
		return Error::ERROR_FAILED;
	}
	int DeleteMovie(const Entity::Movie& movie)
	{		
		return Delete("%s", "SELECT NAME AS MovieName FROM MOVIES WHERE NAME = '" + movie.name + "' "
			"UNION "
			"SELECT MOVIENAME AS MovieName FROM SHOWS WHERE MOVIENAME = '" + movie.name + "'", "DELETE FROM MOVIES WHERE NAME = '" + movie.name + '\'',true);
	}
	int DeleteShow(const std::string& idShow)
	{
		return Delete("%s", "SELECT MOVIENAME FROM SHOWS WHERE ID = " + idShow, "DELETE FROM SHOWS WHERE ID = " + idShow);
	}
	int DeleteBooking(const POINT& coord)
	{
		return Delete("%s", "SELECT USERID FROM BOOKINGS WHERE SEATX = " + std::to_string(coord.x) + " AND SEATY = " + std::to_string(coord.y), 
			"DELETE FROM BOOKINGS WHERE SEATX = " + std::to_string(coord.x) + " AND SEATY = " + std::to_string(coord.y));
	}
}