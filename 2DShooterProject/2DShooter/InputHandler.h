#ifndef __InputHandler__
#define __InputHandler__

#include <SDL.h>
#include <vector>
#include <iostream>
#include "Singleton.h"

#include "Vector2D.h"

enum mouse_buttons { LEFT, MIDDLE, RIGHT };

class InputHandler : public Singleton<InputHandler>
{
public:
	InputHandler(token);

	void init(int joystickDeadZone);
	
	void update();
	void quit();

	bool getJoystickInitialised() { return m_bJoystickInitialised; }

	int getJoy_X_Value(int joyID, int stickSide);
	int getJoy_Y_Value(int joyID, int stickSide);

	bool getButtonState(int joyID, int buttonNumber) { return m_buttonStates[joyID][buttonNumber]; }
	bool getMouseButtonState(int buttonNumber) { return m_mouseButtonStates[buttonNumber]; }
	Vector2Df* getMousePosition() { return m_mousePosition; }

	bool isKeyDown(SDL_Scancode key) const;
	void reset();

private:	
	//functions to handle events
	//keyboard events
	void onKeyDown();
	void onKeyUp();

	//mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	//joystickEvents
	void onJoystickAxisMove(SDL_Event& event);
	void onJoystickButtonDown(SDL_Event& event);
	void onJoystickButtonUp(SDL_Event& event);
	void clearJoysticks();
	
	// member variables

	// joystick specific
	void initialiseJoystick();

	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2Df*, Vector2Df*>> m_jostickAxisValues;
	std::vector<std::vector<bool>> m_buttonStates;

	bool m_bJoystickInitialised;
	int m_joystickDeadZone;

	// mouse specific
	std::vector<bool> m_mouseButtonStates;
	Vector2Df* m_mousePosition;

	// keyboard specific
	const Uint8* m_keyboardState;

};

typedef InputHandler TheInputHandler;

#endif /* defined ( __InputHandler__ ) */