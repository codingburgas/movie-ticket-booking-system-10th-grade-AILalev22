#include "pch.h"
#include "valid.h"
#include "crud.h"
std::unordered_map<Seat, int> seatPrice
{
	{SILVER,5},
	{GOLD,10},
	{PLATINUM,15}
};
std::unordered_map<Seat, std::string> seatType
{
	{SILVER,"Silver"},
	{GOLD,"Gold"},
	{PLATINUM,"Platinum"}
};

int SignUser(Entity::User& acc)
{
	if (LogUser(acc) != Error::ERROR_NOT_EXISTS) return Error::ERROR_EXISTS;
	if (!Validation::IsValidUser(acc)) return Error::ERROR_INPUT;
	return Insert::InsertUser(acc);
}
int LogUser(Entity::User& acc)
{
	return Select::SelectUserExist(acc); // return select db operation result
}