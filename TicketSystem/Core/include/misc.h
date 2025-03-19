#pragma once
#include "memory.h"
#include <new.h>
template<class T>
class AutoPtr
{	
	T* ptr;
	void* memory;
	bool placement;
public:
	AutoPtr(const T& val);
	AutoPtr(T* val) : ptr(val), memory(nullptr)
	{
		placement = false;
	}
	~AutoPtr();
	operator T* ()
	{
		return ptr;
	}
	operator T& ()
	{
		return *ptr;
	}
	T* operator->()
	{
		return ptr;
	}
};
template<class T>
AutoPtr<T>::AutoPtr(const T& val)
{
	memory = ALLOCOBJ(T);
	ptr = new(memory) T(val);
	placement = true;
}
template<class T>
AutoPtr<T>::~AutoPtr()
{
	if (ptr)
	{
		if (!placement)
		{
			Mem::Free(ptr);
			ptr = nullptr;
			return;
		}
		ptr->~T();
	}
	if (memory)
	{
		Mem::Free(memory);
	}
	ptr = nullptr;
}


