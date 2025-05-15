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
	int DeleteShow(const Entity::Show& show)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Query("DELETE FROM SHOWS WHERE DATE = '" + show.date + "\'") ? Error::SUCCESSFUL : Error::ERROR_NOT_EXISTS;
	}
}