#include "misc.h"
#include "pch.h"
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