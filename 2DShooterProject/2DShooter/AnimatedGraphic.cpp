#include "AnimatedGraphic.h"
#include <SDL.h>

void AnimatedGraphic::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);
	refreshTextureVariables();
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw(); // use base class drawing
}

void AnimatedGraphic::update()
{
	if (m_numFrames > 0)
	{
		SDLGameObject::update();
	}
}

void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}