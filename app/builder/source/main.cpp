#include "pch.h"
#include "menu.h"
#include "core\database.h"
#include "main.h"
#include "core\manager.h"
Config conf;
Manager::StruConnector ctorInit;
Manager::StruSMTP smtpInit;
int main()
{
	if (!LoadConfig(conf) || !Manager::Init(ctorInit,smtpInit)) // if startup fails
	{
		Utils::ErrMsg("Internal Error. Please try again later");
		Utils::Exit();
		return 1;
	}

	for(;;)
	switch (Menu::AuthMenu())
	{
	case Menu::ENTER_ADMIN: Menu::AdminMenu(); break;
	case Menu::ENTER_CUSTOMER: Menu::MainMenu(); break;
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
		{
			Utils::DbgMsg("error LoadConfig() env");
			return false;			
		}

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

	ctorInit = { conf.dbhost,conf.dbuser,conf.dbpass,conf.schema};
	smtpInit = { conf.sender,conf.smtpServer };

	return true;
}