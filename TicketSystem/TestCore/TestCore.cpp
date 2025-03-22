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
int main()
{
	Core::Init();
	{
		/*void* mem_conn = Mem::Alloc(sizeof(MySQL::Connector));
		MySQL::Connector* ctor = new (mem_conn) MySQL::Connector("tcp://127.0.0.1:3306", "root", "root1234!!??");
		ctor->Connect();
		ctor->SetDB("dataticket");
		
		char* f = ctor->Read("%d %s %s", "SELECT * FROM TB1 WHERE ID = 1");
		printf("%s", f);
		Mem::Free(f);
		
		ctor->~Connector();
		Mem::Free(mem_conn);*/
		
		Manager::Init("tcp://127.0.0.1:3306", { "root", "root1234!!??" });
		Insert::InsertAccount({ "example", "1234" });
		Manager::Release();
	}
	

	Core::Release();
}

