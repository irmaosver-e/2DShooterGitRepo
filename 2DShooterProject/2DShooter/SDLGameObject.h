#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include <iostream>

class SDLGameObject : public GameObject
{
public:
	virtual ~SDLGameObject() {}

	virtual void load(const LoaderParams& rParams);
	virtual void reset(const LoaderParams& rParams) {} //not implemented in this class
	virtual void draw();
	virtual void update();
	virtual void outOfView();
	virtual void inView();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class
	virtual void collisionPassive() {} //not implemented in this class
	virtual void collisionWithLayer() {} //not implemented in this class

	virtual void addAnimation(std::string& animationID) { m_animations.push_back(animationID); }


	virtual std::string objType() { return "SDLGameObject"; }

protected:
	SDLGameObject();

	void refreshTextureVariables();

	virtual void handleAnimation();
	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;

	std::vector<std::string> m_animations;
};

#endif /* defined( __SDLGameObject__ ) */