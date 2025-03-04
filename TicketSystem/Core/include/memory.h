#pragma once
namespace Mem
{
	// alloc sz number of bytes
	void* Alloc(int sz);
	// reallocate sz number of bytes
	void* Realloc(void* ptr, int sz);
	// free dynamic memory
	void Free(void* ptr);

	// set global heap
	bool Init();
	// destroy global heap
	bool Release();

	// return ptr to first occurance of certain char if found
	void* Find(const void* ptr, char c, int c_ptr);
	// copy size number of bytes from src to dst
	void* Copy(void* dst, const void* src, int size);
	// return ptr to newly allocated copy of src
	void* Duplication(const void* src, int size);
	// set size number of bytes to ptr with a certain char
	void* Set(void* ptr, char c, int size);

	// return index of substr if found in src, if not return -1
	int IndexOf(const void* src, int c_src, const void* what, int c_what);
	// return index of certain char if found in src
	int IndexOf(const void* src, char c, int size);
	// compare buffer p1 with p2 lexicographically, returns 0 if equal, 1 if p1 is bigger, -1 if p1 is smaller 
	int Cmp(const void* p1, const void* p2, size_t n);
}
