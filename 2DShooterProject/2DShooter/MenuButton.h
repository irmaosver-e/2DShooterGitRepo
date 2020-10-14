#ifndef __MenuButton__
#define __MenuButton__

#include "SDLGameObject.h"

class MenuButton :	public SDLGameObject
{
public:
	MenuButton() : SDLGameObject(), m_callback(0), m_bReleased(true), m_bButtonPressed(false) {}
	virtual ~MenuButton() {}

	virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision();
	
	int getCallbackID() { return m_callbackID; }
	void setCallback(void(*callback)()) { m_callback = callback; }

	virtual std::string objType() { return "Player"; }

private:
	enum button_state {MOUSE_OUT, MOUSE_OVER, CLICKED};

	bool m_bButtonPressed;

	void (*m_callback) ();

	bool m_bReleased;

	int m_callbackID;
};

#endif /* defined ( __MenuButton__ ) */
