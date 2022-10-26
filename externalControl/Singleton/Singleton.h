//////////////////////////////////////////////////////////////////////////
// 2012.07.17 Add J.C
//////////////////////////////////////////////////////////////////////////

template<typename T>
class  Singleton
{
private:
	static T* ms_pSingleton;

public:
	Singleton()
	{
		ASSERT( NULL == Singleton<T>::ms_pSingleton);
		Singleton<T>::ms_pSingleton= (T*)this;
	}

	Singleton(Singleton &rhs)
	{
		ASSERT( NULL == Singleton<T>::ms_pSingleton);
		Singleton<T>::ms_pSingleton= (T*)this;
	}
	/*
	Singleton()
	{
		if (ms_pSingleton!=NULL)
			AfxMessageBox("Singleton error");
		
		assert( NULL==Singleton<T>::ms_pSingleton );

		Singleton<T>::ms_pSingleton = (T*)this;
	}

	~Singleton()
	{
		Singleton<T>::ms_pSingleton = NULL;
	}
	*/

	static T* GetSingleton()
	{
		return ms_pSingleton;
	}
};

/*static*/ template<typename T> T* Singleton<T>::ms_pSingleton=NULL;