#ifndef __Layer__
#define __Layer__

#include <iostream>

#include"Vector2D.h"

class Level;

struct ObjectMarker
{
	Vector2Df objStartPosition;
	Vector2Df objPositionMarker;
	std::string objectType;
	std::string objSubType;
	bool isActive;

	void reset()
	{
		objPositionMarker = objStartPosition;
		isActive = true;
	}
};

class Layer
{
public:
	Layer() : m_scrollSpeed(0) {}

	virtual ~Layer(){}

	virtual void render() = 0;
	virtual void update() = 0;

	std::string& getLayerNameRef() { return m_layerName; }
	float& getScrollSpeedRef() { return m_scrollSpeed; }

	float* const getScrollSpeedPtr() { return &m_scrollSpeed; }

protected:

	std::string m_layerName;

	float m_scrollSpeed;

};

#endif /* defined ( __Layer__ ) */