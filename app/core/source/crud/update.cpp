#include "pch.h"

namespace Update
{
	bool UpdateShow(const std::string& idShow,const Entity::Show& show)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		if (shsqlInst->Query("UPDATE SHOWS SET MOVIENAME = '" + show.movieName + "',PRICE = " + std::to_string(show.price) + " ,DATE = '" + show.date + "' WHERE ID = " + idShow))
		{
			return true;
		}

		Utils::DbgMsg("UpdateShow() : query not is ok");
		return false;
	}
}