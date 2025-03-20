// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "string.hpp"
#include <stdio.h>
#include "vector.h"
#include "database.h"
#include "crypt.h" 

#include "misc.h"
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

		typedef Vector<MovedPtr<Vector<Str::String>>> StringArr;
		StringArr vs;
		vs.Add(Vector<Str::String>());
		vs[0]->Add("string");
		vs[0]->Add("hello");

	}
	

	Core::Release();
}

