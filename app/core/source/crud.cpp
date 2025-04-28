#include "pch.h"
#include "crud.h"
#include "crypt.h"
#include "database.h"
#include "manager.h"

namespace Insert
{
	int InsertUser(const Entity::User& acc)
	{
		auto shsql = Manager::GetSQL();

		std::string hemail, hpass;
		Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);

		if (shsql->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", hemail, hpass))
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

namespace Select
{
	int SelectUser(const Entity::User& acc)
	{
		auto shsql = Manager::GetSQL();

		std::string hemail, hpass;
		Crypt::CalcHash(acc.email, hemail); // hash email and pass values
		Crypt::CalcHash(acc.password, hpass);

		std::string retrieved_pass;
		if (shsql->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + hemail + "'", retrieved_pass)) // possible injection, fix later Read
		{
			retrieved_pass.pop_back(); // remove last pipe appended from Read fn
			return retrieved_pass == hpass ? Error::SUCCESSFUL : Error::ERROR_INPUT; // if email is found but password is wrong, return error_input
		}
		return Error::ERROR_NOT_EXISTS; // if email isn't found return error_not_exist
	}
	int SelectMovie(std::string& dst, const std::string& name)
	{
		auto shsql = Manager::GetSQL();

		if (shsql->Read("%s %s %s %d", name.empty() ? "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES" : "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES WHERE NAME = '" + name + '\'', dst))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_NOT_EXISTS;
	}
}

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

namespace Update
{
	bool UpdateShow(const std::string& oldDate,const Entity::Show& show)
	{
		auto shsql = Manager::GetSQL();
		return shsql->Query("UPDATE SHOWS SET MOVIENAME = '" + show.name + "',PRICE = " + std::to_string(show.price) + " ,DATE = '" + show.date + "' WHERE DATE = '" + oldDate + "'");
	}
}