#ifndef __ImageLayer__
#define __ImageLayer__

#include <vector>
#include "Layer.h"
#include "GameObject.h"

class ImageLayer : public Layer
{
public:
	virtual ~ImageLayer();

	virtual void update(Level* pLevel);
	virtual void render();

	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:

	std::vector<GameObject*> m_gameObjects;

};

#endif /* defined ( __ImageLayer__ ) */
