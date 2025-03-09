#include "vector.h"
#include "type.h"
VectorBase::VectorBase(int sz, int szValue)
{
	count = 0;
	len = sz;
	this->szValue = szValue;
	int szAlloc = len * szValue;
	data = Mem::Alloc(szAlloc);
	if (data)
	{
		Mem::Set(data, 0, szAlloc);
	}
	else
		len = 0;
}
VectorBase::~VectorBase()
{
	if (data)
	{
		for (int i = 0; i < count; i++)
		{
			releaseVal((byte*)data + i * szValue);
		}
		Mem::Free(data);
	}
}

bool VectorBase::grow()
{
	return realloc(len + len / 2);
}
void VectorBase::releaseVal(void* val)
{

}
VectorBase::VectorBase(const VectorBase& v)
{
	len = v.len;
	count = v.count;
	szValue = v.szValue;
	data = Mem::Alloc(len * szValue);
	if (data) 
	{
		for (int i = 0; i < count; i++) 
		{
			void* src = (byte*)v.data + i * szValue;
			void* dst = (byte*)data + i * szValue;
			Mem::Copy(dst, src, szValue);
 		}
	}
}
bool VectorBase::realloc(int sz)
{
	if (sz <= count) return false;
	int szAlloc = sz * szValue;
	void* newData = Mem::Realloc(data, szAlloc);
	if (newData)
	{
		data = newData;
		len = sz;
		Mem::Set((byte*)data + len * szValue, 0, szAlloc - len * szValue);
		return true;
	}
	return false;
}
void VectorBase::del(int index)
{
	if (index < 0 || index >= count) return;
	byte* to = (byte*)data + index * szValue;
	releaseVal(to);
	int moved = (count - index - 1) * szValue;
	byte* from = to + szValue;
	Mem::Copy(to, from, moved);
	Mem::Set(to + moved, 0, szValue);
	count--;
}
void* VectorBase::get(int index) const
{
	return (byte*)data + index * szValue;
}
void VectorBase::delAll()
{
	for (int i = 0; i < count; i++)
	{
		releaseVal((byte*)data + i * szValue);
	}
	Mem::Set(data, 0, len * szValue);
	count = 0;
}