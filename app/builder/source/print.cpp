#include "pch.h"
#include "print.h"

namespace Print
{
	void PrintCaption()
	{
        std::ifstream handle(R"(../Presentation/assets/moviesystem.txt)");
        if (!handle.is_open())
        {
            handle.clear();
            handle.open("moviesystem.txt");

            if (!handle.is_open())
            {
                std::cout << "----------MovieSystem----------\n";
                return;
            }
        }

        std::string line;
        while (std::getline(handle, line))
        {
            std::cout << line << std::endl;
        }
        handle.close();
    }
    void PrintRegisterOptions()
    {
        std::cout << "\nOptions:\n1. LogIn\n2. SignUp\n";
    }
}