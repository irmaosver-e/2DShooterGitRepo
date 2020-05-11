#include "InputHandler.h"
#include "Game.h"

//Define static instance
InputHandler* InputHandler::s_pInstance = nullptr;

InputHandler* InputHandler::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new InputHandler();
	}
	return s_pInstance;
}

InputHandler::InputHandler() : m_keyboardState(0),
m_bJoystickInitialised(false),
m_mousePosition(new Vector2D(0, 0))
{
	// create button states for the mouse
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

InputHandler::~InputHandler()
{
	// delete anything we created dynamically
	delete m_keyboardState;
	delete m_mousePosition;

	// clear our arrays
	m_jostickAxisValues.clear();
	m_joysticks.clear();
	m_buttonStates.clear();
	m_mouseButtonStates.clear();
}


bool InputHandler::isKeyDown(SDL_Scancode key) const
{
	if (m_keyboardState != 0)
	{
		if (m_keyboardState[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	return false;
}

void InputHandler::reset()
{
	m_mouseButtonStates[LEFT] = false;
	m_mouseButtonStates[RIGHT] = false;
	m_mouseButtonStates[MIDDLE] = false;
}

void InputHandler::onKeyDown()
{
	m_keyboardState = SDL_GetKeyboardState(0);
}

void InputHandler::onKeyUp()
{
	m_keyboardState = SDL_GetKeyboardState(0);
}

void InputHandler::onMouseMove(SDL_Event& event)
{
	m_mousePosition->setX((float)event.motion.x);
	m_mousePosition->setY((float)event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = true;
	}
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		m_mouseButtonStates[LEFT] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		m_mouseButtonStates[MIDDLE] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		m_mouseButtonStates[RIGHT] = false;
	}
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
	int whichOne = event.jaxis.which; // get which controller
	
	//left stick move left or right
	if (event.jaxis.axis == 0)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].first->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].first->setX(-1);
		}
		else
		{
			m_jostickAxisValues[whichOne].first->setX(0);
		}
	}

	//left stick move up or down
	if (event.jaxis.axis == 1)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].first->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].first->setY(-1);
		}
		else
		{
			m_jostickAxisValues[whichOne].first->setY(0);
		}
	}
		
	//right stick move left or right
	if (event.jaxis.axis == 3)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].second->setX(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].second->setX(-1);
		}
		else
		{
			m_jostickAxisValues[whichOne].second->setX(0);
		}
	}

	//right stick move up or down
	if (event.jaxis.axis == 4)
	{
		if (event.jaxis.value > m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].second->setY(1);
		}
		else if (event.jaxis.value < -m_joystickDeadZone)
		{
			m_jostickAxisValues[whichOne].second->setY(-1);
		}
		else
		{
			m_jostickAxisValues[whichOne].second->setY(0);
		}
	}
}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = true;
}

void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
	int whichOne = event.jaxis.which;

	m_buttonStates[whichOne][event.jbutton.button] = false;
}

void InputHandler::update()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;

		case SDL_JOYAXISMOTION:
			onJoystickAxisMove(event);
			break;

		case SDL_JOYBUTTONDOWN:
			onJoystickButtonDown(event);
			break;

		case SDL_JOYBUTTONUP:
			onJoystickButtonUp(event);
			break;

		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;

		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;

		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;

		case SDL_KEYDOWN:
			onKeyDown();
			break;

		case SDL_KEYUP:
			onKeyUp();
			break;

			default:
                break;
		}
	}
}

void InputHandler::clean()
{
	if(m_bJoystickInitialised)
	{
		for (int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_JoystickClose(m_joysticks[i]);
		}
	}
}

void InputHandler::initialiseJoystick()
{
	if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0)
	{
		SDL_InitSubSystem(SDL_INIT_JOYSTICK);
	}

	if (SDL_NumJoysticks() > 0)
	{
		for ( int i = 0; i < SDL_NumJoysticks(); i++)
		{
			SDL_Joystick* joy = SDL_JoystickOpen(i);

			if (SDL_JoystickGetAttached(joy))
			{
				m_joysticks.push_back(joy);
				m_jostickAxisValues.push_back(std::make_pair(new Vector2D(0, 0), new Vector2D(0, 0)));
				 
				std::vector<bool> tempButtons;
				for (int j = 0; j < SDL_JoystickNumButtons(joy); j++)
				{
					tempButtons.push_back(false);
				}
				m_buttonStates.push_back(tempButtons);
			}
			else 
			{
				std::cout << SDL_GetError();
			}
		}

		SDL_JoystickEventState(SDL_ENABLE);
		m_bJoystickInitialised = true;
	}
	else
	{
		m_bJoystickInitialised = false;
	}
}

int InputHandler::getJoy_X_Value(int joyID, int stickSide)
{
	if (m_joysticks.size() > 0)
	{
		if (stickSide == 1)
		{
			return (int)m_jostickAxisValues[joyID].first->getX();
		}
		else if (stickSide == 2)
		{
			return (int)m_jostickAxisValues[joyID].second->getX();
		}
	}
	return 0;
}

int InputHandler::getJoy_Y_Value(int joyID, int stickSide)
{
	if (m_joysticks.size() > 0)
	{
		if (stickSide == 1)
		{
			return (int)m_jostickAxisValues[joyID].first->getY();
		}
		else if (stickSide == 2)
		{
			return (int)m_jostickAxisValues[joyID].second->getY();
		}
	}
	return 0;
}
