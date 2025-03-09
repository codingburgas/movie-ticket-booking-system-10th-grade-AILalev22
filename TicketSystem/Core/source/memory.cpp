#include "memory.h"
#include "type.h"
#include <tchar.h>
#include <windows.h>

namespace Mem
{
	static HANDLE globalHeap = 0;
	void* AllocHeap(HANDLE heap, int sz)
	{
		if (sz > 0)
			return HeapAlloc(heap, 0, sz);
		return 0;
	}
	void* Alloc(int sz)
	{
		return AllocHeap(globalHeap, sz);
	}

	void* ReallocHeap(HANDLE heap, void* ptr, int sz)
	{
		if (sz > 0)
			return HeapReAlloc(heap, 0, ptr, sz);
		return 0;
	}
	void* Realloc(void* ptr, int sz)
	{
		return ReallocHeap(globalHeap, ptr, sz);
	}

	void FreeHeap(HANDLE heap, void* ptr)
	{
		HeapFree(heap, 0, ptr);
	}
	void Free(void* ptr)
	{
		FreeHeap(globalHeap, ptr);
	}

	bool Init()
	{
		return globalHeap = HeapCreate(0, 0, 0);
	}
	bool Release()
	{
		return HeapDestroy(globalHeap);
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
		return 0;
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
				return *b1 - *b2;
			b1++; b2++;
		}
		return 0;
	}	
}
