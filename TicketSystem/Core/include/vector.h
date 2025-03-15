#include "memory.h"
class VectorBase
{
protected:
	void* data;
	int len;
	int count;
	int szValue;
	void* Get(int index) const;
	bool Grow();
	bool Realloc(int sz);
	virtual void ReleaseVal(void* val);
	VectorBase(const VectorBase&);
	~VectorBase();
public:

	void Del(int index);
	void DelAll();
	VectorBase(int sz, int szValue); 
	const int Size() { return count; }
};
template<class T>
class Vector : public VectorBase
{
	void ReleaseVal(void* val);
public:
	T& Get(int index) const;	
	T* Add(const T& val);
	Vector(int sz);
	Vector();
	Vector(const Vector<T>&);
	T& operator[](int index) const
	{
		return Get(index);
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
void Vector<T>::ReleaseVal(void* val)
{
	((T*)val)->~T();
}
template<class T>
T& Vector<T>::Get(int index) const
{
	return *((T*)VectorBase::Get(index));
}
template<class T>
T* Vector<T>::Add(const T& val)
{
	if (count >= len)
		if (!Grow())
			return 0;
	T& ret = Get(count);
	ret = val;
	count++;
	return& ret;
}


