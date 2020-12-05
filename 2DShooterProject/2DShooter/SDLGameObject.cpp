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
m_bPlayedDeathSound(false),
m_tbAnimationState(END)
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
	trackFrameTime();
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

void SDLGameObject::handleAnimation()
{
	//needs checking, seems redundant, should use play animation instead
	refreshTextureVariables();
	m_currentFrame = (SDL_GetTicks() / m_animSpeed) % m_numFrames;
}

void SDLGameObject::refreshTextureVariables()
{
	m_numFrames = TheTextureManager::Instance().getAnimationFrameCount(m_textureID);
	m_middleFrame = (m_numFrames > 1) ? (m_numFrames / 2) + (m_numFrames % 2) : 0;
	m_animSpeed = TheTextureManager::Instance().getAnimationRef(m_textureID).frameDuration;
}

bool SDLGameObject::playAnimation(int startFrame, int endFrame)
{
	if (m_tbAnimationState == BEGIN)
	{
		if (endFrame < 0)
		{
			endFrame = m_numFrames - 1;
		}
		m_currentFrame = startFrame;
		m_tbAnimationState = MIDDLE;
	}

	if (m_tbAnimationState == MIDDLE)
	{
		int frameStepper = (startFrame - endFrame);
		frameStepper = abs(frameStepper) / frameStepper;

		if (m_bNextFrameOK)
		{
			//test for out of range frame
			int futureFrame = m_currentFrame + frameStepper;

			if (futureFrame >= 0 && futureFrame < m_numFrames)
			{
				m_currentFrame = futureFrame;
				
				if(m_currentFrame == endFrame)
				{
					m_tbAnimationState = END;
				}
			}
			else
			{
				m_tbAnimationState = END;
			}
		}
	}
	
	return (m_tbAnimationState == END);
}

bool SDLGameObject::switchAnimation(int animationID, bool resetFrameCount)
{
	bool animationChanged = false;

	//needs to change to first frame before counting time
	if (m_textureID != m_animations[animationID])
	{
		m_textureID = m_animations[animationID];
		
		refreshTextureVariables();
		resetAnimation(resetFrameCount);

		animationChanged = true;
	}

	return animationChanged;
}

void SDLGameObject::resetAnimation(bool resetFrameCount)
{
	m_frameTime = 0;
	m_bNextFrameOK = false;
	m_tbAnimationState = resetFrameCount ? BEGIN : MIDDLE;
}

void SDLGameObject::trackFrameTime()
{
	m_frameTime += TheSDLSystem::Instance().getFrameTime();
	m_bNextFrameOK = false;


	if (m_frameTime >= m_animSpeed)
	{
		m_bNextFrameOK = true;
		m_frameTime = 0;
	}


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


