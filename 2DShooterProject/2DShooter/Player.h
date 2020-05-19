#ifndef __Player__
#define __Player__

#include "ShooterObject.h"
#include "BaseCreator.h"

class Player : public ShooterObject
{
public:
	Player() : ShooterObject(), 
		m_invulnerable(false),	
		m_invulnerableTime(200),
		m_invulnerableCounter(0)
	{}
	virtual ~Player() {}

	virtual void load(std::unique_ptr<LoaderParams> &pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	
	virtual void collision() {} 

	virtual std::string objType() { return "Player"; }
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