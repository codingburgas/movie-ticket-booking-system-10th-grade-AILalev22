// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.hpp"
#include <stdio.h>
#include "database.hpp"
#include "crypt.hpp" 
#include "misc.hpp"
#include <string>
#include <vector>
#include <iostream>
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
		MySQL::Connector* ctor = new MySQL::Connector("tcp://127.0.0.1:3306", "root", "root1234!!??");
		ctor->Connect();
		ctor->SetDB("dataticket");
		char s[] = "hellosssssssssssssss";
		
	}
	

	Core::Release();
}

