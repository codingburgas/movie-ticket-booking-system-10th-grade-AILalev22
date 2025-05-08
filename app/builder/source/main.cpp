#include "pch.h"
#include "menu.h"
#include "core\database.h"
#include "main.h"
#include "core\manager.h"
int main()
{	
	Config conf; // app configuration
	if (!LoadConfig(conf) || !Manager::Init(conf.dbhost, conf.dbuser, conf.dbpass, conf.schema)) // if startup fails
	{
		Utils::ErrMsg("Internal Error. Please try again later");
		Utils::Exit();
		return 1;
	}
	
	for(;;)
	switch (Menu::AuthMenu(conf))
	{
	case Menu::ENTER_ADMIN: Menu::AdminMenu(); break;
	case Menu::ENTER_CUSTOMER: Menu::MainMenu(conf); break;
	}
}

bool LoadConfig(Config& conf)
{
	char* env[] = 
	{
	getenv(DB_HOST_ENV),
	getenv(DB_PASS_ENV),
	getenv(DB_USER_ENV),
	getenv(SMTP_EMAIL_ENV),
	getenv(SMTP_PASS_ENV)
	};
	for (const auto& e : env)
		if (!e)
			return false;

	conf.ademail = DB_ADMIN_EMAIL;
	conf.cinemas = CINEMAS;
	conf.cols = COL_SIZE;
	conf.schema = DB_SCHEMA;
	conf.halls = HALLS;
	conf.rows = ROW_SIZE;
	conf.smtpServer = SMTP_SERVER;
	conf.dbhost = env[0] ?  env[0] : "";
	conf.dbpass = env[1] ? env[1] : "";
	conf.dbuser = env[2] ? env[2] : "";
	conf.sender.email = env[3] ? env[3] : "";;
	conf.sender.password = env[4] ? env[4] : "";

	return true;
}