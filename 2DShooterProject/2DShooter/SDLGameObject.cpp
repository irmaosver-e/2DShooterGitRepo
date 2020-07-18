#include "SDLGameObject.h"

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
}

void SDLGameObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
	m_position = Vector2D((float)pParams->getX(), (float)pParams->getY());

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();
	m_numFrames = pParams->getNumFrames();
	m_animSpeed = pParams->getAnimSpeed();

	//m_collisionShape
}

void SDLGameObject::draw()
{	
	//TheTextureManager::Instance().drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
	//										m_width, m_height, m_currentRow, m_currentFrame, TheSDLSystem::Instance().getRenderer(), m_angle, m_alpha);
	
	TheTextureManager::Instance().drawTile(m_textureID,2, 2, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame, TheSDLSystem::Instance().getRenderer());
}

void SDLGameObject::update()
{
	m_position += m_velocity;
}

int SDLGameObject::getAnimatedFrame(float speedModifier)
{
	return int(TheSDLSystem::Instance().getRunningTime() / (m_animSpeed / speedModifier)) % m_numFrames;
}

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

