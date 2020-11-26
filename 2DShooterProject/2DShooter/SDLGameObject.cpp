#include "SDLGameObject.h"
#include "Game.h"
#include "TextureManager.h"

#include "SDLSystem.h"

SDLGameObject::SDLGameObject() : GameObject(),
m_bulletFiringSpeed(0),
m_bulletCounter(0),
m_moveSpeed(0),
m_dyingTime(0),
m_dyingCounter(0),
m_bPlayedDeathSound(false)
{
	m_bIsOn = true;
	m_bInView = true;
	m_bUpdating = true;
}

void SDLGameObject::load(const LoaderParams& rParams)
{
	m_position = Vector2Df(rParams.getX(), rParams.getY());

	m_width = rParams.getWidth();
	m_height = rParams.getHeight();
	m_subTypeID = rParams.getSubTypeID();

	m_animations = rParams.getAnimationList();
	if (m_animations.empty())
	{
		m_textureID = m_subTypeID;
	}
	else
	{
		m_textureID = m_animations[0];
	}

	m_sfx = rParams.getSFX();
}

void SDLGameObject::reset(const LoaderParams& rParams)
{
	load(rParams);
	refreshTextureVariables();
	m_currentFrame = 0;
	m_bDying = false;
	m_bDead = false;
	m_bColliding = false;
	m_bulletCounter = 0;
}

void SDLGameObject::draw()
{	
	//TheTextureManager::Instance().drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
	//										m_width, m_height, m_currentRow, m_currentFrame, m_angle, m_alpha);
	
	//if spacing, margin, width and height, are automatic if using animated tile
	TheTextureManager::Instance().drawTile(m_textureID,0, 0, (int)m_position.getX(), (int)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame);
}

void SDLGameObject::update()
{
	if (m_bUpdating)
	{
		m_position += m_velocity;
	}
	handleAnimation();
}

void SDLGameObject::outOfView()
{
	m_bUpdating = false;
}

void SDLGameObject::inView()
{
	m_bUpdating = true;
}

/*
int SDLGameObject::getAnimatedFrame(float speedModifier)
{
	return int(TheSDLSystem::Instance().getRunningTime() / (m_animSpeed / speedModifier)) % m_numFrames;
}
*/


void SDLGameObject::handleAnimation()
{
	refreshTextureVariables();
	m_currentFrame = (SDL_GetTicks() / m_animSpeed) % m_numFrames;
}

void SDLGameObject::refreshTextureVariables()
{
	if (m_lastTextureID != m_textureID)
	{
		m_numFrames = TheTextureManager::Instance().getAnimationFrameCount(m_textureID);
		m_animSpeed = TheTextureManager::Instance().getAnimationRef(m_textureID).frameDuration;

		m_lastTextureID = m_textureID;
	}
}

bool SDLGameObject::playAnimation(int animationID, bool playReverse)
{
	bool animmationFinished = false;
	int frameStepper = 1;

	if(playReverse)
	{
		frameStepper = -1;
	}

	//needs to change to first frame before counting time
	if (m_textureID != m_animations[animationID])
	{
		m_textureID = m_animations[animationID];
		refreshTextureVariables();

		m_currentFrame = 0;
		
		if (playReverse)
		{
			m_currentFrame = (m_numFrames - 1);
		}

		m_frameTime = 0;

	}
	else
	{
		m_frameTime += TheSDLSystem::Instance().getFrameTime();

		if (m_frameTime >= m_animSpeed)
		{
			m_frameTime = 0;
			m_currentFrame += frameStepper;

			//if frame has gone out range the animation ended
			
			if (!playReverse)
			{
				animmationFinished = m_currentFrame >= m_numFrames;
			}
			else
			{
				animmationFinished =  m_currentFrame < 0;
			}
		}
	}

	return animmationFinished;
}

void SDLGameObject::handleDying()
{
	//checks if the dying animation has finished
   	if (m_currentFrame == (m_numFrames - 1))
	{
		m_bDead = true;
		turnObjOff();
	}

	/*
	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++; //simple counter ok w fixed frame rate
	*/
}


