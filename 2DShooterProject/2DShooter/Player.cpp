#include "Player.h"

#include <SDL.h>

#include "Game.h"
#include "SDLSystem.h"
#include "InputHandler.h"
#include "BulletHandler.h"
#include "SoundManager.h"

Player::Player() : SDLGameObject()
{
	m_invulnerable = false;
	m_invulnerableTime = 200;
	m_invulnerableCounter = 0;
	m_lives = 1;
	m_playerHUD = nullptr;
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

void Player::draw()
{
	SDLGameObject::draw();
	m_playerHUD->draw();
}

void Player::update()
{
	//if the level is finished, fly off the screen
	if (TheGame::Instance().getLevelComplete())
	{
		if (m_position.getX() >= TheSDLSystem::Instance().getScreenWidth())
		{
			TheGame::Instance().setCurrentLevel(TheGame::Instance().getCurrentLevel() + 1);
		}
		else
		{
			m_velocity.getXRef() = 3;
			m_velocity.getYRef() = 0;
			SDLGameObject::update();
			handleAnimation();
		}
	}
	else
	{
		//if player NOT in death animation
		if (!m_bDying)
		{
			m_velocity.getXRef() = 0;
			m_velocity.getYRef() = 0;
			handleInput();
			SDLGameObject::update();
			//handleAnimation();
		}
		else //in death animation
		{
			m_currentFrame = int((SDL_GetTicks() / (100)) % m_numFrames);

			//if death animation finished
			if (m_dyingCounter == m_dyingTime)
			{
				ressurect();
			}
			m_dyingCounter++;
		}
	}
}

void Player::collision()
{	
	/*  //godmode for debuging
	
	std::cout << "GOD MODE ON in Player::collision() \n";
	m_invulnerable = true;
	
	*/  //-----------------------
	

	// if the player is not invulnerable then set to dying and change values for death animation tile sheet
	if (!m_invulnerable && !TheGame::Instance().getLevelComplete())
	{
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


void Player::ressurect()
{
	m_lives -= 1;

	m_position.getXRef() = 10;
	m_position.getYRef() = 200;
	m_bDying = false;

	//m_textureID = "player";

	m_currentFrame = 0;
	//m_numFrames = 5;
	//m_width = 101;
	//m_height = 46;

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleInput()
{
	if (!m_bDead)
	{
		// handle keys
		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_UP) && m_position.getY() > 0)
		{
			m_velocity.getYRef() = (float)-m_moveSpeed;
		}
		else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN) && (m_position.getY() + m_height) < TheSDLSystem::Instance().getScreenHeight() - 10)
		{
			m_velocity.getYRef() =(float)m_moveSpeed;
		}

		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT) && m_position.getX() > 0)
		{
			m_velocity.getXRef() = (float)-m_moveSpeed;
		}
		else if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT) && (m_position.getX() + m_width) < TheSDLSystem::Instance().getScreenWidth())
		{
			m_velocity.getXRef() = (float)m_moveSpeed;
		}

		if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_SPACE))
		{
			if (m_bulletCounter == m_bulletFiringSpeed)
			{
				TheSoundManager::Instance().playSound("shoot", 0);
				//TheBulletHandler::Instance().addPlayerBullet((int)m_position.getX() + 90, (int)m_position.getY() + 12, 32, 32, "bulletSmall", 1, Vector2D(10, 0));

				TheBulletHandler::Instance().fireBullet(m_subTypeID, m_position, Vector2Df(10, 0));
				m_bulletCounter = 0;
			}

			m_bulletCounter++;
		}
		else
		{
			m_bulletCounter = m_bulletFiringSpeed;
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

	// ajust animation angle if the player is alive and moving
	if (!m_bDead)
	{
		if (m_velocity.getX() < 0)
		{
			m_angle = -10.0;
		}
		else if (m_velocity.getX() > 0)
		{
			m_angle = 10.0;
		}
		else
		{
			m_angle = 0.0;
		}
	}


	SDLGameObject::handleAnimation();
}
