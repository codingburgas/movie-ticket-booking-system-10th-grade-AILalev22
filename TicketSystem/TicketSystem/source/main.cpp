#include "menu.h"
#include "core.h"
#include "string.h"

int main()
{
	if (!Core::Init()) return 1;
	
	Menu::User* account = Menu::GetChoice(); // get a ptr either to class Customer or Admin

	account->MainMenu(); // call Main menu function, either admin panel or customer menu

	if (account)
	{
		Mem::Free(account);
		account = nullptr;
	}
	Core::Release();
}