#pragma once
#include "memory.h"
#include <new.h>
template<class T>
class AutoPtr
{	
	// generic T type ptr
	mutable T* ptr;
	void* memory;
public:
	AutoPtr(const T& val);
	AutoPtr(T* val) : ptr(val)
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
		ptr = nullptr;
	}
	if (memory)
		Mem::Free(memory);
}
template<class T>
class MovedPtr
{
	// generic T ptr
	mutable T* ptr;
	// placement new mem buff
	mutable void* memory;
public:
	MovedPtr(const T& val);
	MovedPtr(T* val) : memory(nullptr), ptr(val)
	{

	}
	// move constructor
	MovedPtr(const MovedPtr& p)
	{
		ptr = p.ptr;
		p.ptr = nullptr;
		memory = p.memory;
		p.memory = nullptr;
	}
	~MovedPtr();
	// overload to treat obj like reference
	operator T& ()
	{
		return *ptr;
	}
	// overload to treat obj as ptr
	operator T* ()
	{
		return ptr;
	}
	// overload to use arrow operator with obj
	T* operator->()
	{
		return ptr;
	}
	// move assignment operator and check if same ptr is passed
	void operator=(const MovedPtr& p)
	{
		if (this != &p)
		{
			if (ptr)
			{
				ptr->~T();
				ptr = nullptr;
			}
			if (memory)
			{
				Mem::Free(memory);
				memory = nullptr;
			}
			ptr = p.ptr;
			p.ptr = nullptr;
			memory = p.memory;
			p.memory = nullptr;
		}
	}
	// return if generic ptr is valid
	bool IsValid()
	{
		return ptr;
	}
	// return whether mem buff has any allocated memory
	bool isAlloc()
	{
		return memory;
	}
};
template<class T>
MovedPtr<T>::MovedPtr(const T& val)
{
	memory = ALLOCOBJ(T);
	ptr = new(memory) T(val); // using placement new to construct an obj
}

template<class T>
MovedPtr<T>::~MovedPtr()
{
	if (ptr)
	{
		ptr->~T(); // calling T type constructor, because raw memory is used	
		ptr = nullptr;
	}
	if (memory)
		Mem::Free(memory);
}


