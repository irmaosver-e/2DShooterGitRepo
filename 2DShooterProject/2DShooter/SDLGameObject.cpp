#include "SDLGameObject.h"
#include "Game.h"
#include "SDLSystem.h"
#include "TextureManager.h"

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

/*
void SDLGameObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
	m_position = Vector2Df(pParams->getX(), pParams->getY());

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumFrames();
	m_animSpeed = pParams->getAnimSpeed();
	m_sfx = pParams->getSFX();
}
*/

void SDLGameObject::load(const LoaderParams& rParams)
{
	m_position = Vector2Df(rParams.getX(), rParams.getY());

	m_width = rParams.getWidth();
	m_height = rParams.getHeight();
	m_textureID = rParams.getTextureID();
	m_numFrames = rParams.getNumFrames();
	m_animSpeed = rParams.getAnimSpeed();
	m_sfx = rParams.getSFX();
}

void SDLGameObject::draw()
{	
	//TheTextureManager::Instance().drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
	//										m_width, m_height, m_currentRow, m_currentFrame, TheSDLSystem::Instance().getRenderer(), m_angle, m_alpha);
	
	TheTextureManager::Instance().drawTile(m_textureID,2, 2, (int)m_position.getX(), (int)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, TheSDLSystem::Instance().getRenderer());
}

void SDLGameObject::update()
{
	if (m_bUpdating)
	{
		m_position += m_velocity;
	}
}

void SDLGameObject::outOfView()
{
	m_bUpdating = false;

	//scroll speed should be held in map, needs change
	scroll(TheGame::Instance().getScrollSpeed());
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




//to be made redundant
void SDLGameObject::doDyingAnimation()
{
	//keeps scrolling w the map

	m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % m_numFrames);

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++; //simple counter ok w fixed frame rate
}


