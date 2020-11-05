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
	
	//m_numFrames = rParams.getNumFrames();
	//m_animSpeed = rParams.getAnimSpeed();

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

//to be renamed, misleading old name
void SDLGameObject::doDyingAnimation()
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


