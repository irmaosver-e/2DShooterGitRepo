#ifndef __BaseCreator__
#define __BaseCreator__

#include "GameObject.h"

class BaseCreator
{

public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}

};

template <class T> class ObjCreator : public BaseCreator
{
	GameObject* createGameObject() const
	{
		return new T();
	}
};

#endif /* defined ( __BaseCreator__ ) */