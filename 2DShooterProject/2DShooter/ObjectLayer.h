#ifndef __ObjectLayer__
#define __ObjectLayer__

#include <vector>
#include "Layer.h"
#include "GameObject.h"

class ObjectLayer : public Layer
{
public:

	ObjectLayer() : Layer()
	{
		m_bObjCountIncreased = false;
	}

	virtual ~ObjectLayer();

	virtual void update();
	virtual void render();
	
	void reset();
	void resetMarkers();
	void resetObjects();
	void turnObjectsOff();

	std::vector<ObjectMarker>& getObjMarkersRef() { return m_objectMarkers; }
	
	std::vector<GameObject*>* getGameObjects() { return &m_gameObjects; }
	std::vector<GameObject*>& getGameObjectsRef() { return m_gameObjects; }
	bool hasObjectEnteredLayer() { return m_bObjCountIncreased; }
	
	void addObjectToLayer(GameObject* gameObj) { m_gameObjects.push_back(gameObj); }

private:
	std::vector<ObjectMarker> m_objectMarkers;
	std::vector<GameObject*> m_gameObjects;

	bool m_bObjCountIncreased;
};

#endif /* defined ( __ObjectLayer__ ) */