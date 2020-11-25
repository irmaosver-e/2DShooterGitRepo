#ifndef __Singleton__
#define __Singleton__

template<typename T>
class Singleton
{
public:
	static T& Instance();

	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton) = delete;

	virtual ~Singleton() {}

protected:
	struct token {};
	Singleton() {};
};

template<typename T>
T& Singleton<T>::Instance()
{
	static T s_instance{ token{} };
	return s_instance;
}

#endif /* defined(__Singleton__) */
