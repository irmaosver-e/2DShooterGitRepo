#ifndef __Singleton__
#define __Singleton__

template<typename T>
class Singleton
{
public:
	static T& Instance();

	Singleton(const Singleton&) = delete;
	Singleton& operator= (const Singleton) = delete;

protected:
	struct token {};
	Singleton() {};
};

#endif /* defined(__Singleton__) */
