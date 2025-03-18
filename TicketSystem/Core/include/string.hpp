#pragma once
#include "memory.h"
namespace Str
{
	// len of str
	int Len(const char* s);
	// index of certain char in str, returns -1 if not found
	int IndexOf(const char* s, int c);
	// replace old charset in str with new charset
	void ReplaceChars(char* s, const char* olds, const char* news);
	// swap two buffers with equal size
	void Swap(void* a, void* b, size_t n);

	class StringBase
	{
	protected:
		char* data;
		// capacity
		int sz_data;
		// count without '\0
		int c_data;

		// ensure enough space is made, if not realloc data
		bool MakeEnough(int sz);
		// Realloc function based on Mem::Realloc
		bool Realloc(int sz);
		// insert a str at a index position
		char* Insert(int index, const char* str);
		// make a deep copy of a substr, index is start pos, len is size of the substr
		char* Substr(int index, int len);
		virtual ~StringBase();
	public:
		// same as at()
		char operator[](int index)
		{
			return At(index);
		}
		// char* operator()() { return data; }
		// literal constructor
		StringBase(const char* s)
		{
			data = nullptr;
			Assign(s);
		}
		// empty parameter constructor
		StringBase()
		{
			data = nullptr;
			Assign("");
		}
		// capacity constructor
		StringBase(int sz_data);
		// return str
		const char* Cstr() { return data; }
		// return 0 if empty, else 1
		bool Empty() { return !c_data; }
		const int Size() { return c_data; }
		const int Capacity() { return sz_data; }
		// return compare result with a literal
		int Compare(const char* str)
		{
			return Mem::Cmp(data, str, c_data);
		}
		// return compare result with an object
		int Compare(const StringBase& o_str)
		{
			return Mem::Cmp(data, o_str.data, c_data);
		}
		// append a str at the end
		void Append(const char* str)
		{
			Insert(c_data, str);
		}
		// assign a new value to data
		void Assign(const char* str);
		// remove last char
		void PopBack();
		// append several strings to str, must end with 0 to avoid undefined behaviour
		void Join(const char* str, ...);
		// return char at given index
		char At(int index);
		// set all elements as 0
		void Clear();
		// swap with another object
		void Swap(StringBase&);
		// replace at certain index, index is start pos
		void Replace(int index, const char* str);
		// append a single char
		void PushBack(char c);
		// remove a substr from data, index is starting point, if no len given it removes until the end
		void Remove(int index, int len = -1);
	};
	class String : public StringBase
	{
	public:
		String() : StringBase()
		{

		}
		String(const char* str) : StringBase(str)
		{

		}
		String(int sz_data) : StringBase(sz_data)
		{

		}
		String(const String& o_str) : StringBase(o_str.data)
		{

		}
		void operator=(const char* str)
		{
			Assign(str);
		}
		~String() = default;
		// return substr at starting index, if no len given it returns until the end, uses deep copy
		String Substr(int index, int len = -1);
		// insert at a certain index another str, uses current object
		String& Insert(int index, const char* str);
	};
}