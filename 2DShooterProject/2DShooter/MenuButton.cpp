#include "MenuButton.h"
#include "InputHandler.h"
#include "SoundManager.h"

void MenuButton::load(std::unique_ptr<LoaderParams> const& pParams)
{
	SDLGameObject::load(std::move(pParams));
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT; //STARTS AT FRAME 0
}

void MenuButton::draw()
{
	SDLGameObject::draw(); // use base class drawing
}

void MenuButton::update()
{
	if (m_bColliding)
	{
		if (m_bButtonPressed)
		{
			// do some animation

			// do soundFX
			if (!TheSoundManager::Instance().playSoundOnce(m_sfx, (int)this)) // uses memory address "(int)this" as a ID for the object   
			{
				m_bButtonPressed = false;
				
				if (m_callback != 0)
				{
					m_callback();
				}
			}
		}
		else
		{
			m_currentFrame = MOUSE_OVER;
		}

	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}

	/* redundant Respond to mouse pointer directly
	Vector2D* pMousePos = TheInputHandler::Instance().getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width) &&
		pMousePos->getX() > m_position.getX() &&
		pMousePos->getY() < (m_position.getY() + m_height) &&
		pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance().getMouseButtonState(LEFT) && m_bReleased)
		{
			m_currentFrame = CLICKED;

			if (m_callback != 0)
			{
				m_callback();
			}

			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance().getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else 
	{
		m_currentFrame = MOUSE_OUT;
	}
	*/

}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::collision()
{
	if (TheInputHandler::Instance().isKeyDown(SDL_SCANCODE_RETURN))
	{
		m_bButtonPressed = true;
	}
}
