#include "pch.h"

namespace Insert
{
	int InsertUser(const Entity::User& acc)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		std::string hpass;
		//Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);
		return shsqlInst->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", acc.email, hpass) ? Error::SUCCESSFUL : Error::ERROR_EXISTS;		
	}
	int InsertMovie(const Entity::Movie& movie)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Write("%s %s %s %d", "INSERT INTO MOVIES(NAME,GENRE,LANGUAGE,RELEASEYEAR) VALUES(?,?,?,?)",movie.name, movie.genre, movie.language, movie.releaseYear) ? Error::SUCCESSFUL : Error::ERROR_EXISTS;
	}
	int InsertShow(const Entity::Show& show)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Write("%s %s %f", "INSERT INTO SHOWS(MOVIENAME,DATE,PRICE) VALUES(?,?,?)",show.name, show.date, show.price) ? Error::SUCCESSFUL : Error::ERROR_EXISTS;
	}
}