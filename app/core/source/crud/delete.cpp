#include "pch.h"

namespace Delete
{
	int DeleteMovie(const Entity::Movie& movie)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string tmp;
		if (shsqlInst->Read("%s", "SELECT NAME FROM MOVIES WHERE NAME = '" + movie.name + "'", tmp))
		{
			if (shsqlInst->Query("DELETE FROM MOVIES WHERE NAME = '" + movie.name + '\''))
			{
				return Error::SUCCESSFUL;
			}
		}
		return Error::ERROR_NOT_EXISTS;
	}

	int DeleteShow(const std::string& idShow)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string dst;
		if (shsqlInst->Read("%s", "SELECT MOVIENAME FROM SHOWS WHERE ID = " + idShow, dst))
		{
			if (shsqlInst->Query("DELETE FROM SHOWS WHERE ID = " + idShow))
			{
				return Error::SUCCESSFUL;
			}
		}
		return Error::ERROR_NOT_EXISTS;
	}
	int DeleteBooking(const POINT& coord)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string tmp;
		if (shsqlInst->Read("%s", "SELECT USERID FROM BOOKINGS WHERE SEATX = " + std::to_string(coord.x) + " AND SEATY = " + std::to_string(coord.y), tmp))
		{
			if (!tmp.empty())
			{
				if (shsqlInst->Query("DELETE FROM BOOKINGS WHERE SEATX = " + std::to_string(coord.x) + " AND SEATY = " + std::to_string(coord.y)))
				{
					return Error::SUCCESSFUL;
				}
			}
		}
		return Error::ERROR_NOT_EXISTS;
	}
}