#include "Game.h"
#include "ShooterObject.h"
#include "TextureManager.h"

void ShooterObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
	m_position = Vector2D((float)pParams->getX(), (float)pParams->getY());

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();

	m_numFrames = pParams->getNumFrames();
	//m_animSpeed = pParams->getAnimSpeed();
}

void ShooterObject::draw()
{	
	TextureManager::Instance()->drawFrame(m_textureID, (Uint32)m_position.getX(), (Uint32)m_position.getY(),
											m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer(), m_angle, m_alpha);

}

void ShooterObject::update()
{
	m_position += m_velocity;
	m_currentFrame = int(((SDL_GetTicks() / (1000 / 3)) % m_numFrames));
}

void ShooterObject::doDyingAnimation()
{
	//keeps scrolling w the map
	//scroll(TheGame::Instance()->getScrollSpeed());

	m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % m_numFrames);

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++; //simple counter ok w fixed frame rate
}

