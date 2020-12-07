#ifndef __Player__
#define __Player__

#include "SDLGameObject.h"
#include "HUD.h"
#include "ObjectLayer.h"

class Player : public SDLGameObject
{
public:
	Player();
	virtual ~Player();

	virtual void load(const LoaderParams& rParams);
	virtual void reset(const LoaderParams& rParams);

	virtual void draw();
	virtual void update();
	
	virtual void collision();
	virtual void collisionWithLayer();

	void flyOffScreen();
	void flyIntoScreen();

	//player does not scroll empty function
	virtual void scroll(float scrollSpeed) {}
	
	int* getLivesPtr() { return &m_lives; }
	int checkLives() const { return m_lives; }
	bool outOfLives() { return (m_lives > 0) ? false : true; }

	void setHUDPtr(HUD* pHUD) { m_playerHUD = pHUD; }

	virtual std::string objType() { return "Player"; }

private:
	enum stances { SHIP = -1, MECHA = 1 };
	enum animations { NO_ANIM = -1, SHIP_IDLE, MECHA_IDLE, MECHA_ATTACK_TRANSITION, ATTACK_ANIM, TRANSFORM_ANIM, DEATH_ANIM };
	enum actions { NO_ACT, ATTACK_ACT, DEAD_ACT, TRANSFORM_ACT, FLY_OFF_ACT};

	//enum player_x_direction { HORIZ_REST, BACK, PX_FORWARD };
	//enum player_y_direction { VERT_REST, UP, DOWN };
	
	enum V_dir_tribool { TB_UP = -1, TB_V_REST, TB_DOWN };
	enum H_dir_tribool { TB_LEFT = -1, TB_H_REST, TB_RIGHT };

	struct direction_cross
	{
		V_dir_tribool V_direction;
		H_dir_tribool H_direction;
	};

	struct player_input
	{
		direction_cross direction_hat;

		actions action;
	};

	void ressurect();
	void handleInput();
	virtual void handleAnimation();
	void handleMechaAnim();
	void handleShipAnim();

	void handleActions();
	void attackAction();

	void moveAction();

	void flyOffAction();

	void transformRequest();
	void transformAction();
	void transformAnim();

	HUD* m_playerHUD;
	//ObjectLayer* m_pPlayFieldObjLayer;
	//ObjectMarker* m_pPlayerMarker;

	player_input m_requestedInputs;
	actions m_requestedDirectAction;

	actions m_desiredAction;
	animations m_desiredAnimation;
	direction_cross m_desiredAnimation_direction;
	bool m_desired_move_animation_finished;

	actions m_lastAction;

	
	stances m_currentForm;

	int m_lives;

	bool m_invulnerable;
	bool m_bFlyingOffScreen;
	int m_invulnerableTime;
	int m_invulnerableCounter;
};

#endif /*defined(__Player__)*/