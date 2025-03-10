#include "string.hpp"
#include "type.h"
#include <stdarg.h>
namespace Str
{
	int Len(const char* s)
	{
		const char* p = s;
		while (*p) p++;

		return p - s;
	}
	void Swap(void* a, void* b, size_t n)
	{
		using Mem::Copy;
		void* t = Mem::Alloc(n);
		if (!t) return;
		Copy(t, a, n);
		Copy(a, b, n);
		Copy(b, t, n);
		Mem::Free(t);
	}
	int IndexOf(const char* s, int c)
	{
		const char* s2 = s;
		while (*s2)
		{
			if (*s2 == c)
				return s2 - s;
			s2++;
		}
		return -1;
	}
	void ReplaceChars(char* s, const char* olds, const char* news)
	{
		char* str = s;
		int c_subs = Len(olds);
		while (*str)
		{
			int i = IndexOf(olds, *str);
			if (i >= 0)
				*str = news[i];
			str++;
		}
	}
	//////////////////////////////////////////
	StringBase::StringBase(int sz_data)
	{
		this->sz_data = sz_data + 1;
		data = (char*)Mem::Alloc(sz_data + 1);
		Mem::Set(data, 0, sz_data + 1);
		c_data = 0;
	}
	StringBase::~StringBase()
	{
		if (data)
		{
			Mem::Free(data);
			data = nullptr;
		}
	}
	void StringBase::Assign(const char* str)
	{
		if (!str) return;
		if (data)
			Mem::Free(data);
		int c_s = Len(str);

		data = (char*)Mem::Alloc(c_s + 1);
		if (!data) return;

		Mem::Copy(data, str, c_s + 1);
		sz_data = c_data = c_s;
	}
	void StringBase::Join(const char* first, ...)
	{
		const char* str[12];
		int len[12];
		int count = 0;
		int lenRes = 0;
		if (first)
		{
			len[0] = c_data;
			str[0] = data;
			lenRes += c_data;
			len[1] = Len(first);
			str[1] = first;
			lenRes += len[1];
			count += 2;
			va_list va;
			va_start(va, first);
			while (count < 12)
			{
				const char* sn = va_arg(va, const char*);
				if (!sn) break;
				len[count] = Len(sn);
				str[count] = sn;
				lenRes += len[count];
				count++;
			}
			va_end(va);
		}
		if (lenRes == 0) return;
		char* res = (char*)Mem::Alloc(lenRes + 1);
		if (!res) return;
		char* p = res;

		for (int i = 0; i < count; i++)
		{
			Mem::Copy(p, str[i], len[i]);
			p += len[i];
		}
		res[lenRes] = 0;
		Mem::Free(data);
		data = res;
		c_data = sz_data = lenRes;
	}
	char StringBase::At(int index)
	{
		if (index >= 0 && index < c_data)
			return data[index];
		return 0;
	}
	void StringBase::Clear()
	{
		if (data)
		{
			Mem::Set(data, 0, c_data);
			c_data = 0;
		}
	}
	void StringBase::PopBack()
	{
		if (!Empty())
			data[--c_data] = 0;
	}
	void StringBase::Swap(StringBase& str)
	{
		using Str::Swap;
		Swap(&c_data, &str.c_data, sizeof(int));
		Swap(&sz_data, &str.sz_data, sizeof(int));
		Swap(&data, &str.data, c_data > str.c_data ? c_data : str.c_data);
	}
	char* StringBase::Substr(int index, int len)
	{
		if (index < 0 || len <= 0 || index >= c_data) return nullptr;

		if (index + len > c_data)
			len = c_data - index;

		char* sub = (char*)Mem::Alloc(len + 1);
		if (!sub) return nullptr;

		Mem::Copy(sub, data + index, len);
		sub[len] = 0;

		return sub;
	}
	void StringBase::Replace(int index, const char* str)
	{
		int len = Str::Len(str);
		if (len <= 0 || index >= c_data || index < 0 || !str) return;
		if (index + len > c_data) len = c_data - index;
		Mem::Copy(data + index, str, len);
	}
	bool StringBase::MakeEnough(int sz)
	{
		if (sz_data - c_data >= sz) return true;
		int addSize = sz / 2;
		if (addSize < sz_data) addSize = sz;
		return Mem::Realloc(data, addSize + sz_data);
	}
	void StringBase::PushBack(char c)
	{
		char add[2] = { c,0 };
		Append(add);
	}
	char* StringBase::Insert(int index, const char* str)
	{
		int c_str = Str::Len(str);
		if (index < 0 || !str || c_str <= 0 || index > c_data) return nullptr;
		if (!MakeEnough(c_data + c_str)) return nullptr;
		for (int from = c_data, to = c_data + c_str; from >= index; from--, to--)
		{
			data[to] = data[from];
		}
		Mem::Copy(data + index, str, c_str);
		c_data += c_str;
		data[c_data] = 0;
		return data;
	}
	void StringBase::Remove(int index, int len)
	{
		if (index < 0 || index >= c_data) return;
		if (len == -1)
		{
			Mem::Set(data + index + 1, 0, c_data - index + 1);
			c_data = index + 1;
			return;
		}
		if (index + len > c_data)
			len = c_data - index;
		Mem::Copy(data + index, data + index + len, c_data - (index + len));
		c_data -= len;
		data[c_data] = 0;
	}
	String String::Substr(int index, int len)
	{
		if (len == -1) len = c_data - index;
		char* sub = StringBase::Substr(index, len);
		String ret = sub;
		Mem::Free(sub);
		return ret;
	}
	String& String::Insert(int index, const char* str)
	{
		StringBase::Insert(index, str);
		return *this;
	}
}