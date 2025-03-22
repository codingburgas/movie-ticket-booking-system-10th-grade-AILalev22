#pragma once
template<class T>
class AutoPtr
{	
	// generic T type ptr
	mutable T* ptr;
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
class MovedPtr
{
	// generic T ptr
	mutable T* ptr;
public:
	MovedPtr(const T& val);
	MovedPtr(T* val) : ptr(val)
	{

	}
	// move constructor
	MovedPtr(const MovedPtr& p);	
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
	void operator=(const MovedPtr& p);
	// return if generic ptr is valid
	bool IsValid()
	{
		return ptr;
	}
};

template<class T>
AutoPtr<T>::AutoPtr(const T& val)
{
	ptr = new T();
}
template<class T>
AutoPtr<T>::~AutoPtr()
{
	delete ptr;
}
template<class T>
void MovedPtr<T>::operator=(const MovedPtr& p)
{
	if (this != &p)
	{
		if (ptr)
		{
			delete ptr;
		}
		ptr = p.ptr;
		p.ptr = nullptr;
	}
}
template<class T>
MovedPtr<T>::MovedPtr(const MovedPtr& p)
{
	ptr = p.ptr;
	p.ptr = nullptr;
}
template<class T>
MovedPtr<T>::MovedPtr(const T& val)
{
	ptr = new T();
}

template<class T>
MovedPtr<T>::~MovedPtr()
{
	if (ptr)
	{
		delete ptr;
	}	
}



