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
	m_desiredAction = NONE;
	m_currentForm = MECHA;

	m_requestedStance = MECHA_IDLE;
	m_currentStance = MECHA_IDLE;

	m_requestedAction = NONE;
	m_requestedAnimation = NONE;


	m_requested_inputs.direction_hat.H_direction = TB_H_REST;
	m_requested_inputs.direction_hat.V_direction = TB_V_REST;
	m_requested_inputs.action = NONE;

	m_desired_action = NONE;
	m_desired_animation = NO_ANIM;

	m_desired_animation_direction.H_direction = TB_H_REST;
	m_desired_animation_direction.V_direction = TB_V_REST;
	m_desired_move_animation_finished = true;

	m_bFiringBullet = false;
}

Player::~Player()
{
	delete m_playerHUD;
}

void Player::load(const LoaderParams& rParams)
{
	// inherited load function
	SDLGameObject::load(rParams);

	// can set up the players inherited values here
	m_lives = rParams.getLives();

	// set up bullets
	m_bulletFiringSpeed = 13;
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
	if (!m_bFlyingOffScreen)
	{
		m_lives = rParams.getLives();
	}
	
	m_dyingCounter = 0;
	m_invulnerable = false;
	m_bDying = false;
	m_bFlyingOffScreen = false;
}

void Player::draw()
{
	SDLGameObject::draw();
	m_playerHUD->draw();
}

void Player::update()
{
		//if player NOT in death animation
		if (!m_bDying)
		{	
			if (!m_bFlyingOffScreen)
			{
				m_velocity.getXRef() = 0;
				m_velocity.getYRef() = 0;


				handleInput();

			}
		}
		else //in death animation
		{
			//if death animation finished
			if (m_dyingCounter == m_dyingTime)
			{
				ressurect();
			}
			m_dyingCounter++;
		}

		trackFrameTime();
		handleActions();
		handleAnimation();

}

void Player::collision()
{		
	/*
	  //godmode for debuging
	std::cout << "GOD MODE ON in Player::collision() \n";
	m_invulnerable = true;
	*/
	  //-----------------------
		
	if (!m_invulnerable)
	{
		m_currentFrame = BACK;
		m_textureID = m_animations[DEAD];
		//m_textureID = "largeexplosion";
		//m_currentFrame = 0;
		//m_numFrames = 9;
		//m_width = 60;
		//m_height = 60;
		m_bDying = true;
	}
}

void Player::collisionWithLayer()
{
	collision();
}

void Player::flyOffScreen()
{
	if (!m_bFlyingOffScreen)
	{
		//m_textureID = m_animations[IDLE];
		m_currentFrame = FORWARD;
		m_velocity.getXRef() = 0;
		m_velocity.getYRef() = 0;

		m_bFlyingOffScreen = true;
		m_invulnerable = true;
	}

	m_velocity.getXRef() = (float)m_moveSpeed * 2;
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

	m_position.getXRef() = 10;
	m_position.getYRef() = 200;
	m_bDying = false;


	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleInput()
{
	/*
	if (!m_bDead)
	{
	*/


	// handle Vertical move requests
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_UP) && m_requested_inputs.direction_hat.V_direction != TB_DOWN) //stops UP having priority
	{
		m_requested_inputs.direction_hat.V_direction = TB_UP;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_requested_inputs.direction_hat.V_direction = TB_DOWN;
	}
	else
	{
		m_requested_inputs.direction_hat.V_direction = TB_V_REST;
	}
	
	//====================================
	// handle Horizontal move requests
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT) && m_requested_inputs.direction_hat.H_direction != TB_RIGHT) //stops LEFT having priority
	{
		m_requested_inputs.direction_hat.H_direction = TB_LEFT;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT))
	{
		m_requested_inputs.direction_hat.H_direction = TB_RIGHT;
	}
	else
	{
		m_requested_inputs.direction_hat.H_direction = TB_H_REST;
	}

	//===================================
	// handle action request
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_S)) // transform requests prioritised
	{
		m_requested_inputs.action = TRANSFORM_ACT;
		//m_requestedStance = TRANSFORM;
	}
	else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_A))
	{
		m_requested_inputs.action = ATTACK_ACT;
		m_requestedStance = ATTACK;
	}
	else
	{
		m_requested_inputs.action = IDLE_ACT;
		m_requestedStance = IDLE;
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

void Player::handleAnimation()
{

	switch (m_desired_animation)
	{
	case TRANSFORM:
		transformAnim();

		break;
	case MECHA_ATTACK:
		//m_desired_action = ATTACK;
		break;
	default:
		//m_desired_action = IDLE;
		break;
	}


	static int lastRequest = NONE;
	if (m_requestedStance != lastRequest && m_desiredAction == NONE) //(m_desiredAction == -1) no Action being performed
	{
		lastRequest = m_requestedStance;

		switch (m_requestedStance)
		{
		//case TRANSFORM:
			//m_desiredAction = TRANSFORM;
			//break;
		case ATTACK:
			m_desiredAction = ATTACK;
			break;
		case DEAD:
			m_desiredAction = DEAD;
			break;
		default:
			m_desiredAction = IDLE;
		}
	}

	switch (m_currentForm)
	{
	case MECHA:
		handleMechaAnim();
		break;

	case SHIP:
		handleShipAnim();
		break;
	}

	if (m_currentStance == ATTACK && m_desiredAction == NONE)
	{
		m_bFiringBullet = true;
	}
	/*
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

void Player::handleMechaAnim()
{
	if (m_desiredAction == TRANSFORM)
	{
		/*
		m_currentStance = TRANSFORM;

		if (playAnimation(TRANSFORM))
		{
			m_desiredAction = NONE; //action compleated no desired Action

			m_currentForm = SHIP;
			m_currentStance = IDLE;
			
			switchAnimation(SHIP_IDLE);
			
			m_currentFrame = IDLE;
		}
		*/
	}
	else
	{
		if (m_desiredAction == IDLE)
		{
			if (m_currentStance != IDLE)
			{
				switchAnimation(MECHA_ATTACK_TRANSITION);
				if (m_bNextFrameOK)
				{
					m_currentStance = IDLE;
				}
			}
			else
			{
				switchAnimation(IDLE);
				if (m_bNextFrameOK)
				{
					m_desiredAction = -1;
				}
			}
		}
		else if (m_desiredAction == ATTACK)
		{
			if (m_currentStance != ATTACK)
			{
				switchAnimation(MECHA_ATTACK_TRANSITION);
				if (m_bNextFrameOK)
				{
					m_currentStance = ATTACK;
				}
			}
			else
			{
				switchAnimation(ATTACK);
				if (m_bNextFrameOK)
				{
					m_desiredAction = NONE;
				}
			}
		}

		switch (m_horiz_direct)
		{
		case BACK:
			m_currentFrame = BACK;
			break;

		case FORWARD:
			m_currentFrame = FORWARD;
			break;

		default:
			m_currentFrame = HORIZ_REST;
		}
	}
}

void Player::handleShipAnim()
{
	static int startFrame = 0, endFrame = 0;

	//sets the desired animation direction
	if (m_desired_move_animation_finished && 
		m_desired_animation_direction.V_direction != m_requested_inputs.direction_hat.V_direction)
	{
		if (m_desired_animation_direction.V_direction == -m_requested_inputs.direction_hat.V_direction)
		{
			//if the past desired anim is the inverse of the request needs to first go to rest position
			m_desired_animation_direction.V_direction = TB_V_REST;
		}
		else
		{
			m_desired_animation_direction.V_direction = m_requested_inputs.direction_hat.V_direction;
		}

		switch (m_desired_animation_direction.V_direction)
		{
		case TB_UP:
			startFrame = m_middleFrame;
			endFrame = m_numFrames - 1;
			break;
		case TB_DOWN:
			startFrame = m_middleFrame;
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

void Player::handleActions()
{

	//----- deals input action request

	if (m_desired_action == NONE) //no action pending
	{
		switch (m_requested_inputs.action)
		{
		case TRANSFORM_ACT:
			m_desired_action = TRANSFORM_ACT;
			m_desired_animation = TRANSFORM;

			break;
		case ATTACK_ACT:
			m_desired_action = ATTACK_ACT;
			break;
		default:
			m_desired_action = IDLE_ACT;
			break;
		}
	}

	if (m_desired_action == TRANSFORM_ACT && m_desired_animation == NO_ANIM)
	{
		transformAction();
	}

	if (m_desired_action != TRANSFORM_ACT && m_desired_action != DEAD_ACT)
	{
		moveAction();
		fireBulletAction();
	}
}

void Player::fireBulletAction()
{
	if(m_bFiringBullet)
	{
		if (m_bulletCounter == m_bulletFiringSpeed)
		{
			TheSoundManager::Instance().playSound("shoot", 0);

			TheBulletHandler::Instance().fireBullet(m_subTypeID, m_textureID, m_position, Vector2Df(10, 0));
			m_bulletCounter = 0;
			m_bFiringBullet = false;
		}

		m_bulletCounter++;
	}
	else
	{
		m_bulletCounter = m_bulletFiringSpeed;
	}
}

void Player::moveAction()
{
	//----- deals W vertical move request
	bool addVel = true;
	switch (m_requested_inputs.direction_hat.V_direction)
	{
	case TB_UP:
		addVel = (m_position.getY() > 0);
		//m_vert_direct = UP;
		break;

	case TB_DOWN:
		addVel = (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight();
		//m_vert_direct = DOWN;

		break;

	default:
		//m_vert_direct = VERT_REST;
	}

	if (addVel)
	{
		m_velocity.getYRef() = (float)m_moveSpeed * m_requested_inputs.direction_hat.V_direction;
	}

	//----- deals W horizontal move request
	addVel = true;
	switch (m_requested_inputs.direction_hat.H_direction)
	{
	case TB_LEFT:
		addVel = (m_position.getX() > 0);
		//m_horiz_direct = BACK;
		break;

	case TB_RIGHT:
		addVel = (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth();
		//m_horiz_direct = FORWARD;

		break;

	default:
		//m_horiz_direct = HORIZ_REST;
	}

	if (addVel)
	{
		m_velocity.getXRef() = (float)m_moveSpeed * m_requested_inputs.direction_hat.H_direction;
	}

	if (m_bUpdating)
	{
		m_position += m_velocity;
	}
}

void Player::transformAction()
{
	m_currentForm = (stances)(m_currentForm * -1); //inverts form
	m_desired_action = NONE;
}

void Player::transformAnim()
{
	switchAnimation(TRANSFORM);

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
	
	if (playAnimation(TRANSFORM, startFrame, endFrame))
	{
		switchAnimation(nextAnim);

		m_currentFrame = 0;
		m_desired_animation = NO_ANIM;
	}
}
