#ifndef __LoaderParams__
#define __LoaderParams__

#include <iostream>

class LoaderParams
{
public:
	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int callbackID = 0, float animSpeed = 0.0, std::string soundFX = "") : 
		m_x(x), 
		m_y(y), 
		m_width(width), 
		m_height(height), 
		m_textureID(textureID),
		m_numFrames(numFrames),
		m_callbackID(callbackID),
		m_animSpeed(animSpeed),
		m_soundFX(soundFX){}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getNumFrames() const { return m_numFrames; }
	float getAnimSpeed() const { return m_animSpeed; }
	int getCallbackID() const { return m_callbackID; }
	std::string getTextureID() const { return m_textureID; }
	std::string getSFX() const { return m_soundFX; }

private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;
	
	int m_numFrames;
	std::string m_textureID;
	std::string m_soundFX;

	int m_callbackID;
	float m_animSpeed;
};

#endif/* Defined( __LoaderParams__ ) */
