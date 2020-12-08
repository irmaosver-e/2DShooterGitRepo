#include "Player.h"

#include <SDL.h>

#include "Game.h"
#include "SDLSystem.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "SoundManager.h"
 
Player::Player() : SDLGameObject()
{
	m_bFlyingOffScreen = false;
	m_invulnerable = false;
	m_invulnerableTime = 200;
	m_invulnerableCounter = 0;
	m_lives = 1;
	m_playerHUD = nullptr;
	m_currentForm = SHIP;
	
	m_requestedInputs.direction_hat.H_direction = TB_H_REST;
	m_requestedInputs.direction_hat.V_direction = TB_V_REST;
	m_requestedInputs.action = NO_ACT;
	m_requestedDirectAction = NO_ACT;

	m_desiredAction = NO_ACT;
	m_lastAction = NO_ACT;
	m_desiredAnimation = NO_ANIM;

	m_desiredAnimation_direction.H_direction = TB_H_REST;
	m_desiredAnimation_direction.V_direction = TB_V_REST;
	m_desired_move_animation_finished = true;
}

Player::~Player()
{
	delete m_playerHUD;
}

void Player::load(const LoaderParams& rParams)
{
	// inherited load function
	SDLGameObject::load(rParams);
	refreshTextureVariables();
	resetAnimation();
	m_currentFrame = m_middleFrame;

	// can set up the players inherited values here
	m_lives = rParams.getLives();

	// set up bullets
	m_bulletFiringSpeed = 10;
	m_moveSpeed = 3;

	// we want to be able to fire instantly
	m_bulletCounter = m_bulletFiringSpeed;

	// time it takes for death explosion
	m_dyingTime = 100;
}

void Player::reset(const LoaderParams& rParams)
{
	m_position = Vector2Df(rParams.getX(), rParams.getY());
	
	//it hasnt finished the last stage stage, it must be restarting the game
	if (m_requestedDirectAction != FLY_OFF_ACT)
	{
		m_lives = rParams.getLives();
	}
	
	m_dyingCounter = 0;
	m_invulnerable = false;
	m_bDying = false;

	m_requestedDirectAction = NO_ACT;
	m_desiredAction = NO_ACT;
	
}

void Player::draw()
{
	SDLGameObject::draw();
	m_playerHUD->draw();
}

void Player::update()
{
	if (m_bUpdating)
	{
		m_velocity.getXRef() = 0;
		m_velocity.getYRef() = 0;

		handleInput();
	
		trackFrameTime();

		handleRequests();
		handleAnimation();
		handleActions();

		m_position += m_velocity;
	}
}

void Player::collision()
{	
	/*
	  //godmode for debuging
	std::cout << "GOD MODE ON in Player::collision() \n";
	m_invulnerable = true;
	//*/
	  
	//-----------------------
		
	if (!m_invulnerable)
	{
		//m_currentFrame = BACK;
		//m_textureID = m_animations[DEAD];
		
		//m_bDying = true;
		m_requestedDirectAction = DEATH_ACT;
	}
}

void Player::collisionWithLayer()
{
	collision();
}

void Player::flyOffScreen()
{
	m_requestedDirectAction = FLY_OFF_ACT;
}

void Player::flyIntoScreen()
{
	m_dyingCounter = 0;
	m_invulnerable = false;
	m_bDying = false;
	m_bFlyingOffScreen = false;
}

void Player::ressurect()
{
	m_lives -= 1;

	//needs to get reset pos from params
	m_position.getXRef() = 10;
	m_position.getYRef() = 200;

	m_bDying = false;

	m_dyingCounter = 0;
	m_invulnerable = true;

	/* m_invulnerable anim
	//flash alpha if invulnerable
	if (m_invulnerable)
	{
		//finish invulnerability
		if (m_invulnerableCounter == m_invulnerableTime)
		{
			m_invulnerable = false;
			m_invulnerableCounter = 0;
			m_alpha = 255;
		}
		else
		{
			if (m_alpha == 255)
			{
				m_alpha = 0;
			}
			else
			{
				m_alpha = 255;
			}
		}
		m_invulnerableCounter++;
	}
	*/
}

void Player::handleInput()
{
	//---------------------------handle Vertical move requests-------------------------------
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_UP) && m_requestedInputs.direction_hat.V_direction != TB_DOWN) //stops UP having priority
	{
		m_requestedInputs.direction_hat.V_direction = TB_UP;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_requestedInputs.direction_hat.V_direction = TB_DOWN;
	}
	else
	{
		m_requestedInputs.direction_hat.V_direction = TB_V_REST;
	}
	
	//-----------------------------handle Horizontal move requests-------------------------------
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT) && m_requestedInputs.direction_hat.H_direction != TB_RIGHT) //stops LEFT having priority
	{
		m_requestedInputs.direction_hat.H_direction = TB_LEFT;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_requestedInputs.direction_hat.H_direction = TB_RIGHT;
	}
	else
	{
		m_requestedInputs.direction_hat.H_direction = TB_H_REST;
	}

	//------------------------------handle action request----------------------------------------
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_S)) // transform requests prioritised
	{
		m_requestedInputs.action = TRANSFORM_ACT;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_requestedInputs.action = ATTACK_ACT;
	}
	else
	{
		m_requestedInputs.action = NO_ACT;
	}

		// */

		/* handle joysticks /
		if(TheInputHandler::Instance().joysticksInitialised())
		{
			if(TheInputHandler::Instance().getButtonState(0, 2))
			{
				if(m_bulletCounter == m_bulletFiringSpeed)
				{
					TheSoundManager::Instance().playSound("shoot", 0);
					TheBulletHandler::Instance().addPlayerBullet(m_position.getX() + 90, m_position.getY() + 12, 11, 11, "bullet1", 1, Vector2D(10,0));
					m_bulletCounter = 0;
				}

				m_bulletCounter++;
			}
			else
			{
				m_bulletCounter = m_bulletFiringSpeed;
			}

			if((TheInputHandler::Instance().getAxisX(0, 1) > 0 && (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth()) || (TheInputHandler::Instance().getAxisX(0, 1) < 0 && m_position.getX() > 0))
			{
				m_velocity.setX(m_moveSpeed * TheInputHandler::Instance().getAxisX(0, 1));
			}

			if((TheInputHandler::Instance().getAxisY(0, 1) > 0 && (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight() - 10 ) || (TheInputHandler::Instance().getAxisY(0, 1) < 0 && m_position.getY() > 0))
			{
				m_velocity.setY(m_moveSpeed * TheInputHandler::Instance().getAxisY(0, 1));
			}
		}
		//*/

	//}
}

void Player::handleRequests()
{
	//----- handle requests
	if (m_desiredAction == NO_ACT) //no action pending, animations should be finished
	{
		if (m_requestedDirectAction != NO_ACT) //direct actions have priority over input actions
		{
			switch (m_requestedDirectAction)
			{
			case FLY_OFF_ACT:
				m_desiredAction = FLY_OFF_ACT;
				if (m_currentForm == SHIP) // if mecha it will have to transform first
				{
					m_requestedDirectAction = NO_ACT;
				}
				//m_lastAction = FLY_OFF_ACT;
			case DEATH_ACT:
				m_desiredAction = DEATH_ACT;
				m_desiredAnimation = DEATH_ANIM;
				m_requestedDirectAction = NO_ACT;
				//m_lastAction = DEATH_ACT;
			}
		}
		else
		{
			switch (m_requestedInputs.action)
			{
			case TRANSFORM_ACT:
				if (m_lastAction != TRANSFORM_ACT) //prevents actions from spamming if button down
				{
					transformRequest(); //sets the desired action, last action and animation
				}
				break;
			case ATTACK_ACT:
				m_desiredAction = ATTACK_ACT;
				m_lastAction = ATTACK_ACT;
				m_desiredAnimation = ATTACK_ANIM;
				break;

			default:
				if (m_lastAction != ATTACK_ACT && m_currentForm == MECHA)
				{
					// handles returning to mecha idle anim when fire button released
					m_desiredAnimation = MECHA_IDLE;
				}
				m_lastAction = NO_ACT;
				m_bulletCounter = m_bulletFiringSpeed;
			}
		}
	}
}

void Player::handleActions()
{
	//direct actions
	if (m_desiredAction == FLY_OFF_ACT && m_desiredAnimation == NO_ANIM)
	{
		flyOffAction();
	}

	if (m_desiredAction == DEATH_ACT && m_desiredAnimation == NO_ANIM)
	{
		deathAction();
	}

	// input actions only if no direct actions are on
	if (m_desiredAction != DEATH_ACT
		&& m_desiredAction != FLY_OFF_ACT)
	{
		if (m_desiredAction == TRANSFORM_ACT && m_desiredAnimation == NO_ANIM)
		{
			transformAction();
		}

		//only move or attack if tranform action is off
		if (m_desiredAction != TRANSFORM_ACT)
		{
			moveAction();

			if (m_desiredAction == ATTACK_ACT && m_desiredAnimation == NO_ANIM)
			{
				attackAction();
			}

		}
	}
}

void Player::handleAnimation()
{
	switch (m_desiredAnimation)
	{
	case TRANSFORM_ANIM:
		transformAnim();
		break;
	case DEATH_ANIM:
		deathAnim();
		break;
	default:
		//m_desiredAction = IDLE;
		break;
	}

	//handles move and attack anim
	if (m_desiredAnimation != TRANSFORM_ANIM && m_desiredAnimation != DEATH_ANIM)
	{
		switch (m_currentForm)
		{
		case MECHA:
			handleMechaAnim();
			break;

		case SHIP:
			handleShipAnim();
			break;
		}
	}
}

void Player::handleMechaAnim()
{
	//-------------------------------handles action animations--------------------

	//handles attack transition animations
	if (m_desiredAnimation == ATTACK_ANIM || m_desiredAnimation == MECHA_IDLE)
	{
		animations nextAnim = m_desiredAnimation;

		//checks if the anim is not the desired already nor transition
		if (m_textureID != m_animations[MECHA_ATTACK_TRANSITION] && m_textureID != m_animations[m_desiredAnimation])
		{
			//must be either ATTACK_ANIM or MECHA_IDLE
			nextAnim = MECHA_ATTACK_TRANSITION;
		}

		//waits for the frame to pass the switch animation, but dont reset the frame count
		if (m_bNextFrameOK)
		{
			switchAnimation(nextAnim, false);
		}

		//reached the desired animation 
		if (m_textureID == m_animations[m_desiredAnimation])
		{
			m_desiredAnimation = NO_ANIM;
		}

	}

	//--------------------------handles move animations-----------------------

	static int startFrame, endFrame;
	//sets the desired animation direction
	if (m_desired_move_animation_finished &&
		m_desiredAnimation_direction.H_direction != m_requestedInputs.direction_hat.H_direction)
	{
		if (m_desiredAnimation_direction.H_direction == -m_requestedInputs.direction_hat.H_direction)
		{
			//if the past desired anim is the inverse of the request needs to first go to rest position
			m_desiredAnimation_direction.H_direction = TB_H_REST;
		}
		else
		{
			m_desiredAnimation_direction.H_direction = m_requestedInputs.direction_hat.H_direction;
		}

		switch (m_desiredAnimation_direction.H_direction)
		{
		case TB_RIGHT:
			startFrame = m_middleFrame;
			endFrame = m_numFrames - 1;
			break;
		case TB_LEFT:
			startFrame = m_middleFrame;
			endFrame = 0;
			break;
		default: // TB_V_REST
			int frameHolder = startFrame;
			startFrame = endFrame;
			endFrame = frameHolder;

		}

		m_desired_move_animation_finished = false;

		resetAnimation();
	}

	//deals with the desired animation direction
	//checks if there is a animation to perform
	if (!m_desired_move_animation_finished)
	{
		m_desired_move_animation_finished = playAnimation(startFrame, endFrame);
	}	
}

void Player::handleShipAnim()
{
	static int startFrame, endFrame;

	//sets the desired animation direction
	if (m_desired_move_animation_finished && 
		m_desiredAnimation_direction.V_direction != m_requestedInputs.direction_hat.V_direction)
	{
		if (m_desiredAnimation_direction.V_direction == -m_requestedInputs.direction_hat.V_direction)
		{
			//if the past desired anim is the inverse of the request needs to first go to rest position
			m_desiredAnimation_direction.V_direction = TB_V_REST;
		}
		else
		{
			m_desiredAnimation_direction.V_direction = m_requestedInputs.direction_hat.V_direction;
		}

		//sets start and end frames
		switch (m_desiredAnimation_direction.V_direction)
		{
		case TB_UP:
			startFrame = m_middleFrame;
			endFrame = m_numFrames - 1;
			break;
		case TB_DOWN:
			startFrame = m_middleFrame;
			endFrame = 0;
			break;
		default: // TB_V_REST
			int frameHolder = startFrame;
			startFrame = endFrame;
			endFrame = frameHolder;

		}

		m_desired_move_animation_finished = false;

		resetAnimation();
	}

	//deals with the desired animation direction
	//checks if there is a animation to perform
	if (!m_desired_move_animation_finished)
	{
		m_desired_move_animation_finished = playAnimation(startFrame, endFrame);
	}

	//no attack animation for ship
	if (m_desiredAnimation == ATTACK_ANIM)
	{
		m_desiredAnimation = NO_ANIM;
	}
}

void Player::attackAction()
{
	if (m_bulletCounter >= m_bulletFiringSpeed)
	{
		TheSoundManager::Instance().playSound("shoot", 0);

		TheBulletHandler::Instance().fireBullet(m_subTypeID, m_textureID, m_position, Vector2Df(10, 0));
		m_bulletCounter = 0;
	}
	else
	{
		m_bulletCounter++;
	}

	m_desiredAction = NO_ACT;
}

void Player::moveAction()
{
	//----- deals W vertical move request
	bool addVel = true;
	switch (m_requestedInputs.direction_hat.V_direction)
	{
	case TB_UP:
		addVel = (m_position.getY() > 0);
		break;

	case TB_DOWN:
		addVel = (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight();
		break;
	}

	if (addVel)
	{
		m_velocity.getYRef() = (float)m_moveSpeed * m_requestedInputs.direction_hat.V_direction;
	}

	//----- deals W horizontal move request
	addVel = true;
	switch (m_requestedInputs.direction_hat.H_direction)
	{
	case TB_LEFT:
		addVel = (m_position.getX() > 0);
		break;

	case TB_RIGHT:
		addVel = (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth();
		break;
	}

	if (addVel)
	{
		m_velocity.getXRef() = (float)m_moveSpeed * m_requestedInputs.direction_hat.H_direction;
	}
}

void Player::transformAction()
{
	m_currentForm = (stances)(m_currentForm * -1); //inverts form
	m_desiredAction = NO_ACT;
}

void Player::flyOffAction()
{
	m_invulnerable = true;
	if (m_currentForm != SHIP)
	{
		transformRequest();
	}
	else
	{
		m_velocity.getXRef() = (float)m_moveSpeed * 2;
	}
}

void Player::deathAction()
{
	m_lives -= 1;

	//needs to get reset pos from params
	m_position.getXRef() = 10;
	m_position.getYRef() = 200;

	m_invulnerable = true;

	m_desiredAction = NO_ACT;
}

void Player::transformRequest()
{
	m_desiredAction = TRANSFORM_ACT;
	m_lastAction = TRANSFORM_ACT;
	m_desiredAnimation = TRANSFORM_ANIM;
}

void Player::transformAnim()
{
	switchAnimation(TRANSFORM_ANIM);

	int startFrame = 0, endFrame = 0;
	animations nextAnim;

	switch (m_currentForm)
	{
	case SHIP:
		startFrame = m_numFrames - 1;
		nextAnim = MECHA_IDLE;
		break;
	case MECHA:
		endFrame = m_numFrames - 1;
		nextAnim = SHIP_IDLE;
		break;
	}
	
	if (playAnimation(startFrame, endFrame))
	{
		switchAnimation(nextAnim);

		m_currentFrame = m_middleFrame;
		m_desiredAnimation = NO_ANIM;

		m_desired_move_animation_finished = true;
		m_desiredAnimation_direction.V_direction = TB_V_REST;
		m_desiredAnimation_direction.H_direction = TB_H_REST;
	}
}

void Player::deathAnim()
{
	switchAnimation(DEATH_ANIM);

	animations nextAnim;
	switch (m_currentForm)
	{
	case SHIP:
		nextAnim = SHIP_IDLE;
		break;
	case MECHA:
		nextAnim = MECHA_IDLE;
		break;
	}

	if (playAnimation())//play full anim
	{
		switchAnimation(nextAnim);

		m_currentFrame = m_middleFrame;
		m_desiredAnimation = NO_ANIM;
	}	
}