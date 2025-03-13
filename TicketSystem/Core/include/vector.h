#include "memory.h"
class VectorBase
{
protected:
	void* data;
	int len;
	int count;
	int szValue;
	void* get(int index) const;
	bool grow();
	bool realloc(int sz);
	virtual void releaseVal(void* val);
	VectorBase(const VectorBase&);
	~VectorBase();
public:

	void del(int index);
	void delAll();
	VectorBase(int sz, int szValue); 
	const int size() { return count; }
};
template<class T>
class Vector : public VectorBase
{
	void releaseVal(void* val);
public:
	T& get(int index) const;	
	T* add(const T& val);
	Vector(int sz);
	Vector();
	Vector(const Vector<T>&);
	T& operator[](int index) const
	{
		return get(index);
	}
};

template<class T>
Vector<T>::Vector(int sz) : VectorBase(sz,sizeof(T))
{
	
}
template<class T>
Vector<T>::Vector() : VectorBase(10, sizeof(T))
{

}
template<class T>
Vector<T>::Vector(const Vector<T>& v) : VectorBase(v)
{

};
template<class T>
void Vector<T>::releaseVal(void* val)
{
	((T*)val)->~T();
}
template<class T>
T& Vector<T>::get(int index) const
{
	return *((T*)VectorBase::get(index));
}
template<class T>
T* Vector<T>::add(const T& val)
{
	if (count >= len)
		if (!grow())
			return 0;
	T& ret = get(count);
	ret = val;
	count++;
	return& ret;
}


