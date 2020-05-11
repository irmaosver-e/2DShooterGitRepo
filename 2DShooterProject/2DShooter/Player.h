#ifndef __Player__
#define __Player__

#include "ShooterObject.h"
#include "Game.h"
#include "InputHandler.h"
#include "BaseCreator.h"

class Player : public ShooterObject
{
public:
	Player() : ShooterObject() {}

	virtual void load(std::unique_ptr<LoaderParams> &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean() { std::cout << "Player::clean() EMPTY \n"; }
	
	virtual void collision() {} 

private:
	void ressurect();
	void handleInput();
	void handleAnimation();

	bool m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
	GameObject* createGameObject() const {	return new Player();	}
};

#endif /*defined(__Player__)*/