#include "MenuButton.h"
#include "InputHandler.h"

void MenuButton::load(std::unique_ptr<LoaderParams> const& pParams)
{
	ShooterObject::load(std::move(pParams));
	m_callbackID = pParams->getCallbackID();
	m_currentFrame = MOUSE_OUT; //STARTS AT FRAME 0
}

void MenuButton::draw()
{
	ShooterObject::draw(); // use base class drawing
}

void MenuButton::update()
{
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
}

void MenuButton::clean()
{
	ShooterObject::clean();
}
