#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include <iostream>

class SDLGameObject : public GameObject
{
public:
	virtual ~SDLGameObject() {}

	//virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void outOfView();
	virtual void inView();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class
	virtual void collisionPassive() {} //not implemented in this class
	virtual void collisionWithLayer() {} //not implemented in this class

	virtual std::string objType() { return "SDLGameObject"; }

protected:
	SDLGameObject();

	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;
};

#endif /* defined( __SDLGameObject__ ) */