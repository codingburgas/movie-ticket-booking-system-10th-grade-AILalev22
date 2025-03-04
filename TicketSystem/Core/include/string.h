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
	void swap(void* a, void* b, size_t n);

	class StringBase
	{
	protected:
		char* data; // char buffer
		int sz_data; // capacity
		int c_data; // count without '\0'
		
		// ensure enough space is made, if not realloc data
		bool MakeEnough(int sz);
		// insert a str at a index position
		char* insert(int index, const char* str);
		// make a deep copy of a substr, index is start pos, len is size of the substr
		char* substr(int index, int len);
		virtual ~StringBase();
	public:
		// same as at()
		char operator[](int index)
		{
			return at(index);
		}
		// char* operator()() { return data; }
		// literal constructor
		StringBase(const char* s)
		{
			assign(s);
		}
		// empty constructor
		StringBase()
		{
			data = nullptr;
			c_data = sz_data = 0;
		}
		// capacity constructor
		StringBase(int sz_data);
		// return str
		const char* cstr() { return data; }
		// return 0 if empty, else 1
		bool empty() { return !c_data; }
		const int size() { return c_data; }
		// return compare result with a literal
		int compare(const char* str)
		{
			return Mem::Cmp(data, str, c_data);
		}
		// return compare result with an object
		int compare(const StringBase& o_str)
		{
			return Mem::Cmp(data, o_str.data, c_data);
		}
		// append a str at the end
		void append(const char* str)
		{
			join(str, nullptr);
		}
		// assign a new value to data
		void assign(const char* str);
		// remove last char
		void pop_back();
		// append several strings to str, must end with 0 to avoid undefined behaviour
		void join(const char* str, ...);
		// return char at given index
		char at(int index);
		// set all elements as 0
		void clear();
		// swap with another object
		void swap(StringBase&);
		// replace at certain index, index is start pos
		void replace(int index, const char* str);
		// append a single char
		void push_back(char c);
		// remove a substr from data, index is starting point, if no len given it removes until the end
		void remove(int index, int len = -1);
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
			assign(str);
		}
		// return substr at starting index, if no len given it returns until the end, uses deep copy
		String substr(int index, int len = -1);
		// insert at a certain index another str, uses current object
		String& insert(int index, const char* str);
	};
}