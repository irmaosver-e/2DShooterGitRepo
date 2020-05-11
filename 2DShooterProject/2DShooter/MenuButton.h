#ifndef __MenuButton__
#define __MenuButton__

#include "BaseCreator.h"
#include "SDLGameObject.h"
#include "InputHandler.h"

class MenuButton :	public SDLGameObject
{
public:
	MenuButton() : SDLGameObject() {}

	virtual void load(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	
	int getCallbackID() { return m_callbackID; }
	void setCallback(void(*callback)()) { m_callback = callback; }

private:
	enum button_state {MOUSE_OUT, MOUSE_OVER, CLICKED};

	void (*m_callback) ();

	bool m_bReleased;

	int m_callbackID; // temp
};

class MenuButtonCreator : public BaseCreator
{
	GameObject* createGameObject() const { return new MenuButton(); }
};

#endif /* defined ( __MenuButton__ ) */
