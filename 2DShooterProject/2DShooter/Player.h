#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void load(const LoaderParams& rParams);
	virtual void update();
	
	virtual void collision();
	virtual void collisionWithLayer();

	//player does nothing if out of view, other objects follow SDLGameObject::outOfView()
	virtual void outOfView() {}

	int& referLives() { return m_lives; }
	int checkLives() { return m_lives; }
	bool outOfLives() { return (m_lives > 0) ? false : true; }

	virtual std::string objType() { return "Player"; }
private:
	void ressurect();
	void handleInput();
	void handleAnimation();

	int m_lives;

	bool m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

#endif /*defined(__Player__)*/