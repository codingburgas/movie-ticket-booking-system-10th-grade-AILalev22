// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <string>
#include <memory>
#include "database.h"
#include "user.h"
#include "process.h"
#include "manager.h"
#include "core.h"
#include "error.h"
int main()
{
	Core::Init();;
	int is_init = 0;
	if (is_init = Manager::Init("tcp://127.0.0.1:3306", "root", "root1234!!??"))
	{

	}
	if (!is_init)
	{
		printf("Manager is not init");
	}
	else
	{
		Manager::GetSQL()->SetDB("dataticket");
	}
	if (is_init)
	{
		switch(Process::ProcessAccount({"example@gmail.com","pass1234567"}))
		{
		case Error::ERROR_INPUT: printf("Invalid input\n"); break;
		case Error::ERROR_DATABASE: printf("Error in mysql server\n"); break;
		case Error::ERROR_EXISTS: printf("Data already exists\n"); break;
		case Error::SUCCESSFUL: printf("Successful\n"); break;
		default: printf("Unexpected error\n"); break;
		}
	}
	
	Manager::Release();
	Core::Release();
}

