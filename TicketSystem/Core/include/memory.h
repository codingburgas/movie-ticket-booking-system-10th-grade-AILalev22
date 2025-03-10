#pragma once
#include "string.h"
#define ALLOCOBJ(T) (T*)Mem::Alloc(sizeof(T))

namespace Mem
{
	// alloc from global heap
	void* Alloc(int sz);
	// realloc memory on global heap
	void* Realloc(void* ptr,int sz);
	// free memory on global heap
	void Free(void* ptr);

	// set global heap
	bool Init();
	// destroy global heap
	bool Release();

	// return a ptr to first found occurance of c
	void* Find(const void* ptr, char c, int c_ptr);
	// copt src to dst based on size
	void* Copy(void* dst, const void* src, int size);
	// return ptr to deep copy of src
	void* Duplication(const void* src, int size);
	// set size bytes of ptr to c
	void* Set(void* ptr, char c, int size);

	// return index of substr if found, if not -1
	int IndexOf(const void* src, int c_src, const void* what, int c_what);
	// return index of c in src if found, if not return -1
	int IndexOf(const void* src, char c, int size);

	// p1 == p2 -> 0
	// p1 > p2 -> 1
	// p1 < p2 -> -1
	int Cmp(const void* p1, const void* p2,size_t n);

}

