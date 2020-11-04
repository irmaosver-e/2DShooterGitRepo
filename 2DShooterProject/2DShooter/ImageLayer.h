#ifndef __ImageLayer__
#define __ImageLayer__

#include <vector>
#include "Layer.h"
#include "GameObject.h"

class ImageLayer : public Layer
{
public:
	virtual ~ImageLayer();

	virtual void update();
	virtual void render();

	void resetPosition();
	
	Vector2Df& getInitialPosRef() { return m_initialPos; }
	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
	Vector2Df m_initialPos;
	std::vector<GameObject*> m_gameObjects;

};

#endif /* defined ( __ImageLayer__ ) */
