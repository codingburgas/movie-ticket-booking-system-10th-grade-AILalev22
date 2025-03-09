#include "pch.h"
#include "menu.h"
#include "memory.h"
#include <new.h>
#pragma warning(disable : 4996)

namespace Menu
{
	void Customer::MainMenu()
	{
		printf("Customer menu\n");
	}

	void Admin::MainMenu() 
	{
		printf("Admin Panel\n");
	}

	char* GetChoice(User*&acc)
	{
		int choice = 0;
		char* pool = nullptr;
		for(;;)
		{
			printf("Enter your choice:\n0. Exit\n1. Customer Menu\n2. Admin Panel\n:"); // get input
			scanf("%d", &choice);

			switch (choice) // assign ptr address based on choice
			{
			case EXIT: exit(0); break;
			case CUSTOMER_MENU: pool = (char*)Mem::Alloc(sizeof(Customer)); break;
			case ADMIN_MENU: pool = (char*)Mem::Alloc(sizeof(Admin)); break;
			default: printf("Invalid input! Try again!\n"); continue;
			}

			if (choice > 0)
			{
				if (choice == CUSTOMER_MENU)
				{
					acc = new (pool) Customer();
				}
				else if (choice == ADMIN_MENU)
				{
					acc = new (pool) Admin();
				}
				break;
			}
		}
		return pool;
	}
}

