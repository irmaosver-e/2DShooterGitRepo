#include "Player.h"

#include <SDL.h>

void Player::load(std::unique_ptr<LoaderParams>& pParams)
{
	ShooterObject::load(pParams);
}

void Player::draw()
{
	ShooterObject::draw();
}

void Player::update()
{
	//if the level is finished, fly off the screen
	if (TheGame::Instance()->getLevelComplete())
	{
		if (m_position.getX() >= TheGame::Instance()->getGameWidth())
		{
			TheGame::Instance()->setCurrentLevel(TheGame::Instance()->getCurrentLevel() + 1);
		}
		else
		{
			m_velocity.setX(0);
			m_velocity.setY(3);
			ShooterObject::update();
			handleAnimation();
		}
	}
	else
	{
		//if player NOT in death animation
		if (!m_bDying)
		{
			m_velocity.setX(0);
			m_velocity.setY(0);
			handleInput();
			ShooterObject::update();
			handleAnimation();
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

void Player::ressurect()
{
	TheGame::Instance()->setPlayerLives(TheGame::Instance()->getPlayerLives() - 1);
	std::cout << "HARDCODED values in Player::ressurect()";
	
	m_position.setX(10);
	m_position.setY(200);
	m_bDying = false;

	m_textureID = "player";

	m_currentFrame = 0;
	m_numFrames = 5;
	m_width = 101;
	m_height = 46;

	m_dyingCounter = 0;
	m_invulnerable = true;
}

void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()->getMousePosition();

	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity = *target - m_position;
		m_velocity /= 50;
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

	//m_currentFrame = int((SDL_GetTicks() / (100 / m_animSpeed)) % m_numFrames);
	m_currentFrame = int((SDL_GetTicks() / (100)) % m_numFrames);
}
