#include "menu.h"
#include "core.h"
#include "string.h"

int main()
{
	if (!Core::Init()) return 1;
	Menu::User* account;
	char* memory = Menu::GetChoice(account); // get a ptr either to class Customer or Admin

	account->MainMenu(); // call Main menu function, either admin panel or customer menu
	account->~User();
	if (memory)
	{
		Mem::Free(memory);
		memory = nullptr;
	}
	Core::Release();
}