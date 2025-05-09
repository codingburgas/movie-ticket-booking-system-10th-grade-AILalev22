#include "pch.h"

namespace Insert
{
	int InsertUser(const Entity::User& acc)
	{
		auto shsql = Manager::GetSQL();

		std::string hpass;
		//Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);

		if (shsql->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", acc.email, hpass))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_EXISTS;
	}
	int InsertMovie(const Entity::Movie& movie)
	{
		auto shsql = Manager::GetSQL();
		if (shsql->Write("%s %s %s %d", "INSERT INTO MOVIES (NAME,GENRE,LANGUAGE,RELEASEYEAR) VALUES(?,?,?,?)", movie.name, movie.genre, movie.language, movie.releaseYear))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_EXISTS;
	}
	int InsertShow(const Entity::Show& show)
	{
		auto shsql = Manager::GetSQL();
		if (shsql->Write("%s %s %f", "INSERT INTO SHOWS(MOVIENAME,DATE,PRICE) VALUES(?,?,?)", show.name, show.date, show.price))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_EXISTS;
	}
}