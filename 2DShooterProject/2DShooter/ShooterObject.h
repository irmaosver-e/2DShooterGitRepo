#ifndef __ShooterObject__
#define __ShooterObject__

#include "GameObject.h"
#include <iostream>

class ShooterObject : public GameObject
{
public:
	virtual ~ShooterObject() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class

	virtual std::string objType() { return "SDLGameObject"; }

protected:
	ShooterObject() : GameObject(),
						m_bulletFiringSpeed(0),
						m_bulletCounter(0),
						m_moveSpeed(0),
						m_dyingTime(0),
						m_dyingCounter(0),
						m_bPlayedDeathSound(false)
	{}

	void doDyingAnimation();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;
};

#endif /* defined( __ShooterObject__ ) */