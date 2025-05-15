#include "pch.h"

namespace Update
{
	bool UpdateShow(const std::string& oldDate,const Entity::Show& show)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Query("UPDATE SHOWS SET MOVIENAME = '" + show.name + "',PRICE = " + std::to_string(show.price) + " ,DATE = '" + show.date + "' WHERE DATE = '" + oldDate + "'");
	}
}