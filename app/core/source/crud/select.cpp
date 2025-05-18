#include "pch.h"

namespace Select
{
	int SelectUserExist(Entity::User& acc)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		std::string hpass; // hashed password
		//Crypt::CalcHash(acc.email, hemail); // hash email and pass values
		Crypt::CalcHash(acc.password, hpass);

		std::string retrievedPass;
		if (shsqlInst->Read("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", retrievedPass)) // possible injection, fix later Read
		{
			Utils::Trim(retrievedPass,"|",false); // remove last pipe appended from Read fn

			Utils::DbgMsg("SelectUserExist() : %s %s", acc.email.c_str(), retrievedPass.c_str());

			if (retrievedPass == hpass)
			{
				std::string idDst;
				if (shsqlInst->Read("%d", "SELECT ID FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", idDst))
				{
					try
					{
						acc.id = std::stod(idDst);

						Utils::DbgMsg("SelectUserExist() : %d", acc.id);
					}
					catch (...)
					{
						Utils::DbgMsg("error SelectUserExist() id cannot read");
					}
				}
				return Error::SUCCESSFUL;
			}
			return Error::ERROR_INPUT; // if email is found but password is wrong, return error_input
		}
		return Error::ERROR_NOT_EXISTS; // if email isn't found return error_not_exist
	}

	int SelectAllUsersEmail(std::vector<std::string>& vec)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string dst;

		if (shsqlInst->Read("%s", "SELECT EMAIL FROM ACCOUNTS WHERE ID > 1 ORDER BY ID ASC", dst)) // fix later add WHERE ID>=1 for admin
		{
			size_t from = 0,to;

			while ((to = dst.find('|', from)) != std::string::npos)
			{
				std::string email = dst.substr(from, to - from);
				if (!email.empty())
					vec.push_back(email);

				from = to + 1;
			}

			std::string last = dst.substr(from);
			if (!last.empty())
				vec.push_back(last);

			for(const auto& email : vec)
			Utils::DbgMsg("SelectAllUsersEmail() : %s", email.c_str());

			if (!vec.empty())
				return Error::SUCCESSFUL;
		}
		return Error::ERROR_FAILED;
	}

	int SelectMovie(std::string& dst, const std::string& name)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		if (shsqlInst->Read("%s %s %s %d", name.empty() ? "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES" : "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES WHERE NAME = '" + name + '\'', dst))
		{
			Utils::DbgMsg("SelectMovie() : %s", dst.c_str());

			if(!dst.empty())
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_NOT_EXISTS;
	}

	int SelectShows(const std::string& movieName,std::string& dst)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		if (shsqlInst->Read("%d %s %f %s", "SELECT ID,DATE,PRICE,CINEMANAME FROM SHOWS WHERE MOVIENAME = '" + movieName + "'", dst))
		{
			Utils::DbgMsg("SelectShows() : %s", dst.c_str());

			if(!dst.empty())
			return Error::SUCCESSFUL;
		}
		return Error::ERROR_NOT_EXISTS;
	}
	int SelectShow(const int& id,Entity::Show& show)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string dst;
		if (shsqlInst->Read("%s %s %f", "SELECT DATE,CINEMANAME,PRICE FROM SHOWS WHERE ID = " + std::to_string(id),dst))
		{
			if (!dst.empty())
			{
				size_t pos1 = dst.find(',');
				if (pos1 == std::string::npos) return false;

				size_t pos2 = dst.find(',', pos1 + 1);
				if (pos2 == std::string::npos) return false;

				size_t pos3 = dst.find('|', pos2 + 1);
				if (pos3 == std::string::npos) pos3 = dst.length();

				show.date = dst.substr(0, pos1);
				show.cinemaName = dst.substr(pos1 + 1, pos2 - pos1 - 1);
				try
				{
					show.price = std::stof(dst.substr(pos2 + 1, pos3 - pos2 - 1));
				}
				catch (...)
				{
					return Error::ERROR_NOT_EXISTS;
				}
				show.id = id;
				return Error::SUCCESSFUL;
			}
		}
		return Error::ERROR_NOT_EXISTS;
	}
	int SelectBookings(std::vector<Entity::Booking>& bookings,int showId,int hallNumber)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();

		std::string query = "SELECT SHOWID,FINALPRICE,USERID,SEATX,SEATY,SEATTYPE,HALLNUMBER FROM BOOKINGS";

		if (showId > 0)
		{
			query.append(" WHERE SHOWID = " + std::to_string(showId));
			if (hallNumber > 0)
			{
				query += " AND HALLNUMBER = " + std::to_string(hallNumber);
			}
		}
		else
		{
			return Error::ERROR_FAILED;
		}

		std::string dst;
		if (shsqlInst->Read("%d %f %d %d %d %s %d", query, dst) && !dst.empty())
		{
			size_t start = 0, end;
			while ((end = dst.find('|', start)) != std::string::npos)
			{
				std::string record = dst.substr(start, end - start);
				start = end + 1;

				std::stringstream ss(record);
				std::string token;
				Entity::Booking book;

				if (std::getline(ss, token, ',')) book.showId = std::stoi(token);
				if (std::getline(ss, token, ',')) book.finalPrice = std::stof(token);
				if (std::getline(ss, token, ',')) book.userId = std::stoi(token);
				if (std::getline(ss, token, ',')) book.seatX = std::stoi(token);
				if (std::getline(ss, token, ',')) book.seatY = std::stoi(token);
				if (std::getline(ss, token, ',')) book.seatType = token;
				if (std::getline(ss, token, ',')) book.hallNumber = std::stoi(token);

				bookings.push_back(book);
				Utils::DbgMsg("SelectBookings() : %d %f %d %d %d %s %d", book.showId, book.finalPrice, book.userId, book.seatX, book.seatY, book.seatType, book.hallNumber);
			}
			if (start < dst.length())
			{
				std::stringstream ss(dst.substr(start));
				std::string token;
				Entity::Booking book;

				if (std::getline(ss, token, ',')) book.showId = std::stoi(token);
				if (std::getline(ss, token, ',')) book.finalPrice = std::stof(token);
				if (std::getline(ss, token, ',')) book.userId = std::stoi(token);
				if (std::getline(ss, token, ',')) book.seatX = std::stoi(token);
				if (std::getline(ss, token, ',')) book.seatY = std::stoi(token);
				if (std::getline(ss, token, ',')) book.seatType = token;
				if (std::getline(ss, token, ',')) book.hallNumber = std::stoi(token);

				bookings.push_back(book);
				Utils::DbgMsg("SelectBookings() : %d %f %d %d %d %s %d", book.showId, book.finalPrice, book.userId, book.seatX, book.seatY, book.seatType, book.hallNumber);
			}

			return bookings.empty() ? Error::ERROR_NOT_EXISTS : Error::SUCCESSFUL;
		}

		return Error::ERROR_NOT_EXISTS;
	}
	int SelectBookings(std::string& dst, int userId)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		std::string raw;
		std::string query = "SELECT SHOWID,FINALPRICE,SEATX,SEATY,SEATTYPE,HALLNUMBER FROM BOOKINGS WHERE USERID = '" + std::to_string(userId) + "'";

		if (shsqlInst->Read("%d %f %d %d %s %d", query, raw) && !raw.empty())
		{
			std::stringstream input(raw);
			std::stringstream output;
			std::string record;

			while (std::getline(input, record, '|'))
			{
				std::stringstream row(record);
				std::string token;
				int fieldIndex = 0;

				while (std::getline(row, token, ','))
				{
					if (fieldIndex == 1)
					{
						float price = std::stof(token);
						output << std::fixed << std::setprecision(2) << price;
					}
					else
					{
						output << token;
					}

					if (++fieldIndex < 6) output << ",";
				}
				output << "|";
			}

			dst = output.str();
			if (!dst.empty()) return Error::SUCCESSFUL;
		}

		return Error::ERROR_NOT_EXISTS;
	}
}