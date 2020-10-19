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

	std::vector<ObjectMarker>& getObjMarkersRef() { return m_objectMarkers; }
	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }

private:
	std::vector<ObjectMarker> m_objectMarkers;
	std::vector<GameObject*> m_gameObjects;

};

#endif /* defined ( __ImageLayer__ ) */
