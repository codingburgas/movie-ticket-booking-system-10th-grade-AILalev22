#pragma once
#include "string.h"
namespace Mem
{
	void* Alloc(int sz);
	void* Realloc(void* ptr,int sz);
	void Free(void* ptr);

	bool Init();
	bool Release();

	void* Find(const void* ptr, char c, int c_ptr);
	void* Copy(void* dst, const void* src, int size);
	void* Duplication(const void* src, int size);
	void* Set(void* ptr, char c, int size);

	int IndexOf(const void* src, int c_src, const void* what, int c_what);
	int IndexOf(const void* src, char c, int size);

	int Cmp(const void* p1, const void* p2,size_t n);

}

