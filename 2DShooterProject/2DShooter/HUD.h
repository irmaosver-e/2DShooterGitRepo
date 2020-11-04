#ifndef __HUD__
#define __HUD__

#include "SDLGameObject.h"

class HUD : public SDLGameObject
{
public:
	HUD() : SDLGameObject() {}
	virtual ~HUD();

	virtual void draw();

	void addTextBox(GameObject* textBox) { m_textBoxes.push_back(textBox); }
	void addAnimGraphix(GameObject* animGraphix) { m_animGraphics.push_back(animGraphix); }

	virtual std::string objType() { return "HUD"; }

private:

	std::vector<GameObject*> m_animGraphics;
	std::vector<GameObject*> m_textBoxes;

};

#endif /* defined ( __HUD__ ) */