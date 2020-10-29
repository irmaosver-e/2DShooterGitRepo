#include "AnimatedGraphic.h"
#include <SDL.h>

void AnimatedGraphic::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);
	m_animSpeed = rParams.getAnimSpeed();
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw(); // use base class drawing
}

void AnimatedGraphic::update()
{
	//m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}