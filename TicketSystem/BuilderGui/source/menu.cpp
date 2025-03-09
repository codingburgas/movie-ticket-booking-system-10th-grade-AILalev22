#include "pch.h"
#include "menu.h"

namespace Menu
{
	// main menu handle to admin window
	static HMENU h_admin  = nullptr;
	// main menu handle to customer window
	static HMENU h_customer = nullptr;

	bool Init()
	{
		if (!h_admin)	
			h_admin = CreateMenu();
		if (!h_customer)
			h_customer = CreateMenu();
		if (h_admin && h_customer) return true;
		return false;
	}
	bool Release()
	{
		if (h_admin)
		{
			DestroyMenu(h_admin);
			h_admin = nullptr;
		}
		if (h_customer)
		{
			DestroyMenu(h_customer);
			h_customer = nullptr;
		}
		if (!h_admin && !h_customer) return true;
		return false;
	}
	void SetHandle(HWND h_wnd, int wnd)
	{
		switch (wnd)
		{
		case ADMIN_WINDOW: SetMenu(h_wnd, h_admin); return;
		case CUSTOMER_WINDOW: SetMenu(h_wnd, h_customer); return;
		default: return;
		}
	}
	void Menu::Create()
	{
		if (!h_admin && !h_customer || h_menu) return;
		if (wnd < ADMIN_WINDOW || wnd > CUSTOMER_WINDOW) return;
		h_menu = CreateMenu();
		AppendMenu(wnd == ADMIN_WINDOW ? h_admin : h_customer, MF_POPUP, (UINT)h_menu, name);
	}
	Menu::Menu(PCSTR name, int wnd)
	{
		this->name = name;
		this->wnd = wnd;
		h_menu = nullptr;
		count = 0;
	}
	Menu::~Menu()
	{
		if (h_menu)
			DestroyMenu(h_menu);
	}
	void Menu::AppendOpt(PCSTR name, int id)
	{
		if (count > MAX_OPTIONS) return;
		count++;
		AppendMenu(h_menu, MF_STRING, id, name);
	}
	void Menu::AppendSep()
	{
		if (count > MAX_OPTIONS) return;
		AppendMenu(h_menu, MF_SEPARATOR, NULL, NULL);
	}

	void AddMenuAdmin()
	{
		// add admin menus and options
	}

	void AddMenuCustomer()
	{
		// add customer menus and options
	}
}