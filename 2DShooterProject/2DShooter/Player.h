#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void load(std::unique_ptr<LoaderParams> const &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	
	virtual void collision();
	int checkLives() { return m_lives; }

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