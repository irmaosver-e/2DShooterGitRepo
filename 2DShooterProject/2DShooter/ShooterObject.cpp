#include "Game.h"
#include "ShooterObject.h"
#include "TextureManager.h"

void ShooterObject::load(std::unique_ptr<LoaderParams> const& pParams)
{
	m_position = Vector2D((float)pParams->getX(), (float)pParams->getY());
	m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = pParams->getWidth();
	m_height = pParams->getHeight();
	m_textureID = pParams->getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
	m_numFrames = pParams->getNumFrames();
	m_animSpeed = pParams->getAnimSpeed();
}

void ShooterObject::draw()
{	
	SDL_RendererFlip flipImage;

	if (m_velocity.getX() > 0)
	{
		flipImage = SDL_FLIP_HORIZONTAL;
	}
	else
	{
		flipImage = SDL_FLIP_NONE;
	}

	TheTextureManager::Instance()->drawFrame(m_textureID,
		(int)m_position.getX(), (int)m_position.getY(),
		m_width, m_height, m_currentRow, m_currentFrame,
		TheGame::Instance()->getRenderer(), flipImage);

}

void ShooterObject::update()
{
	m_velocity += m_acceleration;
	m_position += m_velocity;
}

void ShooterObject::doDyingAnimation()
{
	//keeps scrolling w the map
	scroll(TheGame::Instance()->getScrollSpeed());

	m_currentFrame = int((SDL_GetTicks() / (1000 / 3)) % m_numFrames);

	if (m_dyingCounter == m_dyingTime)
	{
		m_bDead = true;
	}
	m_dyingCounter++; //simple counter ok w fixed frame rate
}

