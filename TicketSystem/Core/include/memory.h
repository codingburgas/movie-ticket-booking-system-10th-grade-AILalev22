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

	class Data
	{
		void* data;
		int c_data;
		int sz_data;

	public:
		Data(int sz = 0);
		Data(const Data&);
		~Data();

		void* ptr() const { return data; }
		byte* p_byte() const { return (byte*)data; }
		char* p_char() const { return (char*)data; }
		int Size() const { return c_data; }
		int Capacity() const { return sz_data; }

		void SetLen(int sz);
		void AddLen(int sz);

		bool MakeEnough(int sz);
		bool Realloc(int sz);

		bool Append(const void* ptr, int c_ptr);
		bool AppendStr(const char* s, int c_s);

		void Submem(int index, int len);

		bool Insert(int index, const void* ptr, int c_ptr);
		void Remove(int index, int len);



	};
}

