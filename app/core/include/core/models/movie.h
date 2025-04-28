#pragma once

namespace Entity
{
	struct Movie
	{
		// main info
		std::string name;
		std::string genre;
		int releaseYear;
		std::string language;

		Movie() : releaseYear(-1) {}
	};
}