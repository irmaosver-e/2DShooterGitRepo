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
	m_desiredAction = -1;
	m_currentForm = MECHA;
	m_requestedStance = IDLE;
	m_currentStance = IDLE;
	m_horiz_direct = HORIZ_REST;
	m_vert_direct = VERT_REST;

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

				if (m_currentStance != TRANSFORM)
				{
					handleInput();
				}
			}

			SDLGameObject::update();
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
		handleAnimation();

		handleBulletFiring();
}

void Player::collision()
{		
	  //godmode for debuging
	std::cout << "GOD MODE ON in Player::collision() \n";
	m_invulnerable = true;
	
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
		m_textureID = m_animations[IDLE];
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
	if (!m_bDead)
	{
		//no key pressed
		m_requestedStance = IDLE;
		
		// handle keys
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
		{
			m_velocity.getYRef() = (float)-m_moveSpeed;
			m_vert_direct = UP;
		}
		else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight() - 10)
		{
			m_velocity.getYRef() =(float)m_moveSpeed;
			m_vert_direct = DOWN;
		}
		else
		{
			m_vert_direct = VERT_REST;
		}

		
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
		{
			m_velocity.getXRef() = (float)-m_moveSpeed;
			m_horiz_direct = BACK;
		}
		else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth())
		{
			m_velocity.getXRef() = (float)m_moveSpeed;

			m_horiz_direct = FORWARD;
		}
		else
		{
			m_horiz_direct = HORIZ_REST;
		}

		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LALT))
		{
			m_requestedStance = TRANSFORM;
		}

		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_SPACE))
		{
			m_requestedStance = ATTACK;
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

	}
}

void Player::handleAnimation()
{
	static int lastRequest = -1;

	if (m_requestedStance != lastRequest && m_desiredAction == -1) //(m_desiredAction == -1) no Action being performed
	{
		lastRequest = m_requestedStance;

		switch (m_requestedStance)
		{
		case TRANSFORM:
			m_currentStance = TRANSFORM;
			m_desiredAction = TRANSFORM;
			break;
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

	if (m_currentStance == ATTACK && m_desiredAction == -1)
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
		if (playAnimation(3)) //TRANSFORM anim Index
		{
			m_desiredAction = -1; //action compleated no desired Action

			m_currentForm = SHIP;
			m_currentStance = IDLE;
			
			switchAnimation(4);
			
			m_currentFrame = 0;
		}
	}
	else
	{
		if (m_desiredAction == IDLE)
		{
			if (m_currentStance != IDLE)
			{
				switchAnimation(7);
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
				switchAnimation(7);
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
					m_desiredAction = -1;
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
	if (m_desiredAction == TRANSFORM)
	{
		if (playAnimation(3, true)) //morph anim Index
		{
			//here when the animation finished
			m_desiredAction = -1; //action compleated no desired Action

			m_currentStance = IDLE;
			m_currentForm = MECHA;

			switchAnimation(0);
			
			m_currentFrame = 0;
		}
	}
	else
	{
		if (m_desiredAction == IDLE)
		{
			m_desiredAction = -1;
			m_textureID = m_animations[4]; //ship texture
			m_currentFrame = 0;
		}
		else if (m_desiredAction == ATTACK)
		{
			m_desiredAction = -1;
			m_currentStance = ATTACK;
		}
	}
}

void Player::handleBulletFiring()
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
