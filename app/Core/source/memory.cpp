#include "pch.h"
#include "type.h"
#include "memory.h"
namespace Mem
{
	int Len(const void* src)
	{
		return Len((void*)src);
	}
	int Len(void* src)
	{
		byte* bsrc = (byte*)src;
		int res = 0;
		while (*bsrc++) res++;
		return res;
	}
	void* Alloc(int sz)
	{
		return ::operator new(sz);
	}
	void Free(void* ptr)
	{
		::operator delete(ptr);
	}

	void* Realloc(void* mem,int sz)
	{
		void* newData = nullptr;
		if (mem)
		{
			int oldLen = Len(mem);
		    newData = Alloc(sz);
			Mem::Copy(newData, mem, oldLen);
			delete mem;
		}
		return newData;
	}
	void* Find(const void* src, char c, int size)
	{
		if (!src || size <= 0) return nullptr;
		byte* p = (byte*)src;
		while (size--)
		{
			if (*p == c)
				return p;
			p++;
		}
		return nullptr;
	}
	void* Copy(void* dst, const void* src, int size)
	{
		byte* to = (byte*)dst;
		byte* from = (byte*)src;
		if (dst && src && size > 0)
		{
			while (size--) *to++ = *from++;
		}
		return dst;
	}
	void* Duplication(const void* src, int size)
	{
		if (!src || size <= 0) return nullptr;;
		void* result = Alloc(size);
		if (result)
		{
			Copy(result, src, size);
		}
		return result;
	}
	void* Set(void* ptr, char c,int size)
	{
		if (!ptr || size <= 0) return ptr;
		byte* src = (byte*)ptr;
		for (int i = 0; i < size; i++, src++)
			*src = c;
		return ptr;
	}

	int IndexOf(const void* src, int c_src, const void* what, int c_what)
	{
		if (!src || c_src <= 0 || !what || c_what <= 0) return -1;
		int index = -1;
		byte* s = (byte*)src;
		byte* sub = (byte*)what;
		for (int i = 0; i < c_src; i++)
		{
			int j = 0;
			for (; j < c_what; j++)
			{
				if (s[i + j] != sub[j]) break;
			}
			if (j >= c_what)
			{
				index = i;
				break;
			}
		}
		return index;
	}
	int IndexOf(const void* ptr, char c, int size)
	{
		char* p = (char*)Find(ptr, c, size);
		if (p)
			return p - (char*)ptr;
		return -1;
	}

	int Cmp(const void* p1, const void* p2, size_t n)
	{
		if (!p1)
		{
			if (p2)
				return -1;
			else
				return 0;
		}
		else
		{
			if (!p2)
				return 1;
		}
		const byte* b1 = (byte*)p1;
		const byte* b2 = (byte*)p2;
		while (n--)
		{
			if (*b1 != *b2)
			{
				if (*b1 - *b2 > 0)
					return 1;
				if (*b1 - *b2 < 0)
					return -1;
			}
			b1++; b2++;
		}
		return 0;
	}
	//////////////////////////////////////////////////////
	Data::Data(int sz)
	{
		if (sz <= 0)
		{
			sz_data = 0;
			data = nullptr;
		}
		else
		{
			data = Alloc(sz);
			if (data)
				sz_data = sz;
			else
				sz_data = 0;

		}
		c_data = 0;
	}
	Data::Data(const Data& instance)
	{
		data = instance.data;
		c_data = instance.c_data;
		sz_data = instance.sz_data;
	}
	Data::~Data()
	{
		Free(data);
	}
	void Data::SetLen(int sz)
	{
		c_data = sz;
		if (sz < 0)
			c_data = 0;
		else if (sz > sz_data)
			c_data = sz_data;
	}
	void Data::AddLen(int sz)
	{
		c_data += sz;
		if (c_data < 0)
			c_data = 0;
		if (c_data > sz_data)
			c_data = sz_data;
	}
	bool Data::MakeEnough(int sz)
	{
		if (sz_data - c_data >= sz) return true;
		int addSize = sz_data / 2;
		if (addSize < sz) addSize = sz;

		return Realloc(addSize + sz_data);
	}
	bool Data::Realloc(int sz)
	{
		if (sz <= 0) return false;
		void* newData = Mem::Realloc(data, sz);
		if (newData)
		{
			data = newData;
			sz_data = sz;
			return true;
		}
		return false;
	}
	bool Data::Append(const void* ptr, int c_ptr)
	{
		if (MakeEnough(c_ptr))
		{
			Mem::Copy((byte*)data + c_data, ptr, c_ptr);
			c_data += c_ptr;
			return true;
		}
		return false;
	}
	bool Data::AppendStr(const char* s, int c_s)
	{
		if (s)
			return Append(s, c_s + 1);
		else
		{
			char empty[1] = { 0 };
			return Append(empty, 1);
		}
	}
	void Data::Submem(int index, int len)
	{
		if (index >= 0)
		{
			if (index < c_data)
			{
				if (len > c_data - index) len = c_data - index;
				Mem::Copy(data, (byte*)data + index, len);
				c_data = len;
			}
			else
			{
				c_data = 0;
			}
		}
	}

	bool Data::Insert(int index, const void* ptr, int c_ptr)
	{
		if (index < 0 || !ptr || c_ptr <= 0 || index > c_data) return false;
		if (!MakeEnough(c_ptr)) return false;
		byte* bp = (byte*)data;
		for (int from = c_data, to = c_data + c_ptr; from >= index; from--, to--)
		{
			bp[to] = bp[from];
		}
		Mem::Copy(bp + index, ptr, c_ptr);
		c_data += c_ptr;
		return true;
	}
	void Data::Remove(int index, int len)
	{
		if (index < 0 || len <= 0 || index >= c_data) return;
		if (index + len > c_data) len = c_data - index;
		Mem::Copy((byte*)data + index, (byte*)data + index + len, c_data - (index + len));
		c_data -= len;
	}
}
