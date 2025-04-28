#pragma once

namespace Entity
{
	// display of certain movie
	struct Show
	{
		// movie name
		std::string name;
		// date in YYYY-MM-DD HH:MM:SS format
		std::string date;
		// price
		double price;

		Show() : price(-1) {}
	};
}