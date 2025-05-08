#include "pch.h"

namespace Delete
{
	int DeleteMovie(const Entity::Movie& movie)
	{
		auto shsql = Manager::GetSQL();
		std::string tmp;
		if (shsql->Read("%s", "SELECT NAME FROM MOVIES WHERE NAME = '" + movie.name + "'", tmp))
		{
			if (shsql->Query("DELETE FROM MOVIES WHERE NAME = '" + movie.name + '\''))
			{
				return Error::SUCCESSFUL;
			}
		}
		return Error::ERROR_NOT_EXISTS;
	}
	int DeleteShow(const Entity::Show& show)
	{
		auto shsql = Manager::GetSQL();
		return shsql->Query("DELETE FROM SHOWS WHERE DATE = '" + show.date + "\'") ? Error::SUCCESSFUL : Error::ERROR_NOT_EXISTS;
	}
}