#include "pch.h"

namespace Insert
{
	int Insert(const std::string& fmt, const std::string& query, ...)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		va_list va;
		va_start(va, &query);

		return shsqlInst->Write(fmt, query, va) ? Error::SUCCESSFUL : Error::ERROR_EXISTS;
	}
	int InsertUser(const Entity::User& acc)
	{
		std::string hpass; // hashed passwword

		Crypt::CalcHash(acc.password, hpass);
		return Insert("%s %s", "INSERT INTO ACCOUNTS(EMAIL,PASSWORD) VALUES(?,?)", &acc.email, &hpass);		
	}
	int InsertMovie(const Entity::Movie& movie)
	{
		return Insert("%s %s %s %d", "INSERT INTO MOVIES(NAME,GENRE,LANGUAGE,RELEASEYEAR) VALUES(?,?,?,?)",&movie.name, &movie.genre, &movie.language, movie.releaseYear);
	}
	int InsertShow(const Entity::Show& show)
	{
		return Insert("%s %s %f %s", "INSERT INTO SHOWS(MOVIENAME,DATE,PRICE,CINEMANAME) VALUES(?,?,?,?)", &show.movieName, &show.date, show.price, &show.cinemaName);
	}
	int InsertBooking(const Entity::Booking& book)
	{
		return Insert("%d %f %d %d %d %s %d", "INSERT INTO BOOKINGS(SHOWID,FINALPRICE,USERID,SEATX,SEATY,SEATTYPE,HALLNUMBER) VALUES(?,?,?,?,?,?,?)", book.showId, book.finalPrice, book.userId, book.seatX, book.seatY, &book.seatType, book.hallNumber);
	}
}