// TestCore.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "core.h"
#include "string.hpp"
#include <stdio.h>
#include "vector.h"
#include "database.h"
#include "new.h"
// String //
//append -> ok
// assgin -> ok
// At -> ok (works with index)
// Clear -> ok
// Compare -> ok
// Cstr -> ok
// Empty -> ok
// Insert -> ok (works with pos, 1 indexing)
// Join -> ok
// operator [] -> ok
// operator = -> ok
// PopBack -> ok
// PushBack -> ok
// Remove -> ok (works with index,after index remove)
//Replace -> ok (works with index)
// Substr -> ok (works with index)
// Swap -> ok (works with obj)

// Data
// Insert -> ok
// other ok


//Vector
// ok


int main()
{
	Core::Init();
	{
		void* mem_conn = Mem::Alloc(sizeof(MySQL::Connector));
		MySQL::Connector* ctor = new (mem_conn) MySQL::Connector("127.0.0.1", "root", "root1234!!??");
		
	}
	Core::Release();
}


