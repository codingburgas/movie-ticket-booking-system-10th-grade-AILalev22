#include "pch.h"
#include "main.h"
#include "menu.h"
#include "core\database.h"
#include "dal\manager.h"
int main()
{
	Config conf; // global app configuration

	if (!Manager::Init(conf.dbhost, conf.dbuser, conf.dbpass,conf.dbname)) // init db manager
	{
		Utils::ErrMsg("Internal Error. Please try again later");
		Utils::Exit();
		return 1;
	}
	
	Menu::AuthMenu();
	Menu::MainMenu();
}