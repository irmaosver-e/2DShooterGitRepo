#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"
#include "HUD.h"

class Player : public SDLGameObject
{
public:
	Player();
	virtual ~Player() {}

	virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	
	virtual void collision();
	virtual void collisionWithLayer();

	//player does not scroll empty function
	virtual void scroll(float scrollSpeed) {}

	int* getLivesPtr() { return &m_lives; }
	int checkLives() const { return m_lives; }
	bool outOfLives() { return (m_lives > 0) ? false : true; }

	void setHUDPtr(HUD* pHUD) { m_playerHUD = pHUD; }

	virtual std::string objType() { return "Player"; }

private:
	enum player_move { BACK, IDLE, FORWARD };
	enum player_stance { STAND, ATTACK, DAMAGE };

	void ressurect();
	void handleInput();
	virtual void handleAnimation();

	HUD* m_playerHUD;

	int m_lives;

	bool m_invulnerable;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

#endif /*defined(__Player__)*/