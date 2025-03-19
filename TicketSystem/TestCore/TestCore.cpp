// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "string.hpp"
#include <stdio.h>
#include "vector.h"
#include "database.h"
#include "new.h"
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
	
		Vector<AutoPtr<Str::String>> vi;
		vi.Add(Str::String("hello"));
		const char* a = vi[0]->Cstr();
		printf("%s",a);
		// doesn't work vector of autoptr
		
	}
	
	Core::Release();
}

