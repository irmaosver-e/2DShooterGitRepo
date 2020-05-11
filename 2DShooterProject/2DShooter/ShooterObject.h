#ifndef __Shooterbject__
#define __ShooterObject__

#include "GameObject.h"
#include "Vector2D.h"

#include <iostream>

class ShooterObject : public GameObject
{
public:
	~ShooterObject() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class

	virtual std::string objType() { return "SDLGameObject"; }

protected:
	ShooterObject();

	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;
};

#endif /* defined( __ShooterObject__ ) */