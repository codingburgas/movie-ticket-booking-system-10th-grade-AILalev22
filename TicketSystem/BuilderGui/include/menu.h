#pragma once

// max options in each menu
#define MAX_OPTIONS 10

namespace Menu
{
	enum
	{
		ADMIN_WINDOW,
		CUSTOMER_WINDOW
	};
	// add all menus to admin window
	void AddMenuAdmin();
	// add all menus to customer window
	void AddMenuCustomer();
	// create and initialize main menu handles for window
	bool Init();
	// destroy main menu handles for window
	bool Release();
	// set main handle for window hwnd
	void SetHandle(HWND h_wnd, int wnd);
	class Menu
	{
		// handle to menu
		HMENU h_menu;
		// count of menu options
		int count;
		// menu name
		PCSTR name;	
		int wnd;
	public:
		Menu(PCSTR name, int wnd);
		~Menu();
		// append the menu to the main menu handle
		void Create();
		// add option in menu options
		void AppendOpt(PCSTR name,int id);
		// add seperator in menu options
		void AppendSep();	
	};
}
// init - create - append - sethandle(hwnd,n) - release