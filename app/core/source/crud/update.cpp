#include "pch.h"

namespace Update
{
	bool Update(const std::string& query)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Query(query);
	}
	bool UpdateShow(const std::string& idShow,const Entity::Show& show)
	{
		std::string query = "UPDATE SHOWS SET MOVIENAME = '" + show.movieName + "',PRICE = " + std::to_string(show.price) + " ,DATE = '" + show.date + "',CINEMANAME = '" + show.cinemaName + "' WHERE ID = " + idShow;

		bool ret = Update(query);

		if(!ret)
		DbgMsg("UpdateShow() : query not is ok");

		return ret;
	}
}