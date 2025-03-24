#pragma once

namespace Mem
{
	int Len(const void* src);
	int Len(void* src);
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
		// mem buffer
		void* data;
		// size
		int c_data;
		//capacity
		int sz_data;

	public:
		Data(int sz = 0);
		Data(const Data&);
		~Data();

		void* ptr() const { return data; }
		byte* p_byte() const { return (byte*)data; }
		char* p_char() const { return (char*)data; }
		// return number of elements
		int Size() const { return c_data; }
		// return total allocated size
		int Capacity() const { return sz_data; }

		// set count if within borders
		void SetLen(int sz);
		// add count if within buff borders
		void AddLen(int sz);

		// grow buffer if sz size is not available
		// tries with 50% of sz_data first
		bool MakeEnough(int sz);
		bool Realloc(int sz);

		// append another buff
		bool Append(const void* ptr, int c_ptr);
		// append a str
		bool AppendStr(const char* s, int c_s);

		// make the buffer to be a submem of itself
		void Submem(int index, int len);

		// insert another buffer at passed index
		bool Insert(int index, const void* ptr, int c_ptr);
		// remove from buffer
		void Remove(int index, int len);

	};
}


