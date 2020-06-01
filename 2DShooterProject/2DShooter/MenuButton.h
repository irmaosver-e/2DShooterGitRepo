#ifndef __MenuButton__
#define __MenuButton__

#include "ShooterObject.h"

class MenuButton :	public ShooterObject
{
public:
	MenuButton() : ShooterObject(), m_callback(0), m_bReleased(true) {}
	virtual ~MenuButton() {}

	virtual void load(std::unique_ptr<LoaderParams> const& pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	
	int getCallbackID() { return m_callbackID; }
	void setCallback(void(*callback)()) { m_callback = callback; }

private:
	enum button_state {MOUSE_OUT, MOUSE_OVER, CLICKED};

	void (*m_callback) ();

	bool m_bReleased;

	int m_callbackID;
};

#endif /* defined ( __MenuButton__ ) */
