#include "stdafx.h"

template<typename T>
Singleton<T>::Singleton()
{
	assert( NULL==Singleton<T>::ms_pSingleton );
	Singleton<T>::ms_pSingleton = (T*)this;
}

Singleton::~Singleton()
{
	Singleton<T>::ms_pSingleton = NULL;
}

Singleton::T* GetSingleton()
{
	return ms_pSingleton;
}