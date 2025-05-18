#include "pch.h"

namespace Select
{
	int Select(const std::string& fmt, const std::string& query, std::string& dst)
	{
		auto shsqlInst = Manager::GetSQL()->GetInstance();
		return shsqlInst->Read(fmt, query, dst) ? Error::SUCCESSFUL : Error::ERROR_NOT_EXISTS;
	}
	int SelectUserExist(Entity::User& acc)
	{
		std::string hpass;
		Crypt::CalcHash(acc.password, hpass);
		std::string retrievedPass;

		int ret = Select("%s", "SELECT PASSWORD FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", retrievedPass);
		if (ret != Error::ERROR_NOT_EXISTS)
		{
			Utils::Trim(retrievedPass, "|", false); // remove last pipe appended from Read fn

			Utils::DbgMsg("SelectUserExist() : %s %s", acc.email.c_str(), retrievedPass.c_str());
			ret = Error::ERROR_INPUT; // if email is found but password is wrong, return error_input

			if (retrievedPass == hpass)
			{
				std::string idDst;
				if (Select("%d", "SELECT ID FROM ACCOUNTS WHERE EMAIL = '" + acc.email + "'", idDst) != Error::ERROR_NOT_EXISTS)
				{
					try
					{
						acc.id = std::stod(idDst); // assign user id
						Utils::DbgMsg("SelectUserExist() : %d", acc.id);
						ret = Error::SUCCESSFUL;
					}
					catch (...)
					{
						Utils::DbgMsg("error SelectUserExist() id cannot read");
						ret = Error::ERROR_FAILED;
					}
				}
			}
		}
		return ret;
	}

	int SelectAllUsersEmail(std::vector<std::string>& vec)
	{
		std::string dst;
		int ret = Error::ERROR_FAILED;

		if (Select("%s", "SELECT EMAIL FROM ACCOUNTS WHERE ID > 1 ORDER BY ID ASC", dst) == Error::SUCCESSFUL)
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
				ret = Error::SUCCESSFUL;
		}
		return ret;
	}

	int SelectMovie(std::string& dst, const std::string& name)
	{
		int ret = Error::ERROR_NOT_EXISTS;
		if (Select("%s %s %s %d", name.empty() ? "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES" : "SELECT NAME,GENRE,LANGUAGE,RELEASEYEAR FROM MOVIES WHERE NAME = '" + name + '\'', dst) == Error::SUCCESSFUL)
		{
			Utils::DbgMsg("SelectMovie() : %s", dst.c_str());

			if(!dst.empty())
			ret = Error::SUCCESSFUL;
		}
		return ret;
	}

	int SelectShows(const std::string& movieName,std::vector<Entity::Show>& shows)
	{
		int ret = Error::ERROR_NOT_EXISTS;

		std::string dst;
		if (Select("%d %s %f %s", "SELECT ID,DATE,PRICE,CINEMANAME FROM SHOWS WHERE MOVIENAME = '" + movieName + "'", dst) == Error::SUCCESSFUL) 
		{
			Utils::DbgMsg("SelectShows() : %s", dst.c_str());

			if (!dst.empty())
			{
				std::stringstream ss(dst);
				std::string showEntry;

				while (std::getline(ss, showEntry, '|')) 
				{
					std::stringstream entryStream(showEntry);
					std::string field;

					Entity::Show s;
					s.movieName = movieName;

					std::getline(entryStream, field, ','); s.id = std::stoi(field);
					std::getline(entryStream, field, ','); s.date = field;
					std::getline(entryStream, field, ','); s.price = std::stof(field);
					std::getline(entryStream, field, ','); s.cinemaName = field;

					shows.push_back(s);
				}

				ret = Error::SUCCESSFUL;
			}
		}
		return ret;
	}
	int SelectShows(const std::string& movieName, std::string& dst)
	{
		int ret = Error::ERROR_NOT_EXISTS;
		if (Select("%d %s %f %s", "SELECT ID,DATE,PRICE,CINEMANAME FROM SHOWS WHERE MOVIENAME = '" + movieName + "'", dst) == Error::SUCCESSFUL)
		{
			Utils::DbgMsg("SelectShows() : %s", dst.c_str());

			if (!dst.empty())
				ret = Error::SUCCESSFUL;
		}
		return ret;
	}
	int SelectShow(const int& id,Entity::Show& show)
	{
		int ret = Error::ERROR_NOT_EXISTS;
		std::string dst;
		if (Select("%s %s %f", "SELECT DATE,CINEMANAME,PRICE FROM SHOWS WHERE ID = " + std::to_string(id),dst) == Error::SUCCESSFUL)
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
					return ret;
				}
				show.id = id;

				ret = Error::SUCCESSFUL;
			}
		}
		return ret;
	}
	int SelectBookings(std::vector<Entity::Booking>& bookings, int showId, int hallNumber)
	{
		int ret = Error::ERROR_FAILED;

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
			return ret;
		}

		std::string dst;
		ret = Error::ERROR_NOT_EXISTS;

		if (Select("%d %f %d %d %d %s %d", query, dst) == Error::SUCCESSFUL&& !dst.empty())
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

			ret = bookings.empty() ? Error::ERROR_NOT_EXISTS : Error::SUCCESSFUL;
		}

		return ret;
	}
	int SelectBookings(std::string& dst, int userId)
	{
		int ret = Error::ERROR_NOT_EXISTS;

		std::string raw;
		std::string query = "SELECT SHOWID,FINALPRICE,SEATX,SEATY,SEATTYPE,HALLNUMBER FROM BOOKINGS WHERE USERID = '" + std::to_string(userId) + "'";

		if (Select("%d %f %d %d %s %d", query, raw) == Error::SUCCESSFUL && !raw.empty())
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
			if (!dst.empty()) ret = Error::SUCCESSFUL;
		}

		return ret;
	}
}