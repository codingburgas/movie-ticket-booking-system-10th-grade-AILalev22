#include "pch.h"

namespace Insert
{
	int InsertUser(const Entity::User& acc)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		std::string hpass;
		//Crypt::CalcHash(acc.email, hemail);
		Crypt::CalcHash(acc.password, hpass);
		return shsqlInst->Write("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", &acc.email, &hpass) ? Error::SUCCESSFUL : Error::ERROR_EXISTS;		
	}

	int InsertMovie(const Entity::Movie& movie)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Write("%s %s %s %d", "INSERT INTO MOVIES(NAME,GENRE,LANGUAGE,RELEASEYEAR) VALUES(?,?,?,?)",&movie.name, &movie.genre, &movie.language, movie.releaseYear) ? Error::SUCCESSFUL : Error::ERROR_EXISTS;
	}

	int InsertShow(const Entity::Show& show)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		std::string dst;
		if (shsqlInst->Write("%s %s %f %s", "INSERT INTO SHOWS(MOVIENAME,DATE,PRICE,CINEMANAME) VALUES(?,?,?,?)", &show.movieName, &show.date, show.price,&show.cinemaName))
		{
			return Error::SUCCESSFUL; // show is inserted correctly
		}
		return Error::ERROR_EXISTS; // show already exists at the passed date
	}

	/*int InsertBooking(const Entity::Booking& book)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		if (shsqlInst->Write("%d %d %f %s", "INSERT INTO BOOKINGS(SHOWID,SEAT,FINALPRICE,STATUS) VALUES(?,?,?,?)", book.showId, book.seat, book.finalPrice, book.status))
		{
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_EXISTS;
	}*/
}