#ifndef __Layer__
#define __Layer__

#include <iostream>

class Level;

class Layer
{
public:
	virtual ~Layer() {}

	virtual void render() = 0;
	virtual void update(Level* pLevel) = 0;

	std::string& refLayerName() { return m_layerName; }

private:
	std::string m_layerName;
};

#endif /* defined ( __Layer__ ) */