// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "string.hpp"
#include <stdio.h>
#include "vector.h"
#include "database.h"
#include "new.h"
#include "crypt.h" 

int main()
{
	Core::Init();
	{
		void* mem_conn = Mem::Alloc(sizeof(MySQL::Connector));
		MySQL::Connector* ctor = new (mem_conn) MySQL::Connector("tcp://127.0.0.1:3306", "root", "root1234!!??");
		ctor->Connect();
		ctor->SetDB("dataticket");
		
		ctor->Write("%s %s", "INSERT INTO TB1(Username,Password) VALUES(?,?)","1111","2222");
		
		
		ctor->~Connector();
		Mem::Free(mem_conn);
	
	
	}
	Core::Release();
}


