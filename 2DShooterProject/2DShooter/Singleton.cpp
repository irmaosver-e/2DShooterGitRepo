#include "Singleton.h"

template<typename T>
T& Singleton<T>::Instance()
{
	static T s_instance{ token{} };
	return s_instance;
}