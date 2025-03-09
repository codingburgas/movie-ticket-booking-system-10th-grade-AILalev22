#pragma once
namespace Menu
{
	enum
	{
		EXIT,
		CUSTOMER_MENU,
		ADMIN_MENU
	};
	// abstract user class
	class User
	{		
	public:
		virtual void MainMenu() = 0;
		virtual ~User() = default;
	};
	
	// customer class
	class Customer : public User
	{
	public:
		// customer menu handling function
		void MainMenu();
	};

	// admin class
	class Admin : public User
	{
	public:
		// admin panel handling function
		void MainMenu();
	};

	// get menu choice
	char* GetChoice(User*&);
}
