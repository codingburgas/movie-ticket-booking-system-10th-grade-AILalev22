// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include <stdio.h>
#include "database.h"
#include "crypt.h"
#include <string>
#include <vector>
#include <iostream>
#include "manager.h"
#include "insert.h"
#include "find.h"
#include "valid.h"
int main()
{
	Core::Init();
	Manager::Init("tcp://127.0.0.1:3306", "root","root1234!!??" );
	std::cout << Insert::InsertAccount({ "abcde@gmail.com","123456789" });


	Manager::Release();
	Core::Release();
}

