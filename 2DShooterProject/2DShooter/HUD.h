#ifndef __HUD__
#define __HUD__

#include "SDLGameObject.h"

class HUD : public SDLGameObject
{
public:
	HUD() : SDLGameObject() {}
	virtual ~HUD() {}

	//virtual void load(const LoaderParams& rParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void addTextBox(GameObject* textBox) { m_textBoxes.push_back(textBox); }

	virtual std::string objType() { return "HUD"; }

private:

	std::vector<GameObject*> m_animGraphics;
	std::vector<GameObject*> m_textBoxes;

};

#endif /* defined ( __HUD__ ) */