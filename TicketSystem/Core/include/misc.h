#pragma once
#include "memory.h"
#include <new.h>
template<class T>
class AutoPtr
{	
	T* ptr;
	void* memory;
public:
	AutoPtr(const T& val);
	AutoPtr(T* val) : ptr(val), memory(nullptr)
	{

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
}
template<class T>
AutoPtr<T>::~AutoPtr()
{
	if (ptr) 
	{
		ptr->~T();
	}
	if (memory)
	{
		Mem::Free(memory);
	}
}

