#include "pch.h"
#include "utils.h"

namespace Utils
{
	void Exit()
	{
		ErrMsg("Quiting!");
		exit(0);
	}
	void ErrMsg(const std::string& msg, int sec)
	{
		if (sec <= 0) sec = 1;

		Clear();
		std::cout << msg << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(sec));
		Clear();
	}
	void Clear()
	{
		system("cls"); 
	}
	void EnterNumber(std::string& num)
	{
		while (true)
		{
			std::cout << ":";
			std::cin >> num;
			if (std::all_of(num.begin(), num.end(), isdigit))
			{
				if (std::stoi(num) > 0)
					break; // break if num is a non-negative number
			}
		}
	}
}