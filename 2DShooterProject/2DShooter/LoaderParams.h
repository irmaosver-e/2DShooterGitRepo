#ifndef __LoaderParams__
#define __LoaderParams__

#include <iostream>

class LoaderParams
{
public:
	LoaderParams() :
		m_x(0),
		m_y(0),
		m_width(0),
		m_height(0),
		m_textureID("none"),
		m_numFrames(1),
		m_lives(1),
		m_callbackID(0),
		m_animSpeed(1),
		m_soundFX("none") {}

	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int lives = 1, int callbackID = 0, float animSpeed = 1, std::string soundFX = "", std::string defaultBullet = "") :
		m_x(x), 
		m_y(y), 
		m_width(width), 
		m_height(height), 
		m_textureID(textureID),
		m_numFrames(numFrames),
		m_lives(lives),
		m_callbackID(callbackID),
		m_animSpeed(animSpeed),
		m_soundFX(soundFX),
		m_defaultBullet(defaultBullet) {}

	LoaderParams(int x, int y, int width, int height, std::string textureID, int numFrames, int lives = 1, float animSpeed = 1, std::string soundFX = "") :
		m_x(x),
		m_y(y),
		m_width(width),
		m_height(height),
		m_textureID(textureID),
		m_numFrames(numFrames),
		m_lives(lives),
		m_animSpeed(animSpeed),
		m_soundFX(soundFX) {}

	int getX() const { return m_x; }
 	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getNumFrames() const { return m_numFrames; }
	float getAnimSpeed() const { return m_animSpeed; }
	int getCallbackID() const { return m_callbackID; }
	int getLives() const { return m_lives; }
	std::string getTextureID() const { return m_textureID; }
	std::string getSFX() const { return m_soundFX; }

	int* ptrX() { return &m_x; }
	int* ptrY() { return &m_y; }
	int* ptrWidth() { return &m_width; }
	int* ptrHeight() { return &m_height; }
	int* ptrNumFrames() { return &m_numFrames; }
	float* ptrAnimSpeed() { return &m_animSpeed; }
	int* ptrCallbackID() { return &m_callbackID; }
	int* ptrLives() { return &m_lives; }
	std::string& refTextureID() { return m_textureID; }
	std::string& refSFX() { return m_soundFX; }
	std::string& refDefaultBullet() { return m_defaultBullet; }

private:

	int m_x;
	int m_y;

	int m_width;
	int m_height;
	
	int m_numFrames;
	std::string m_textureID;
	std::string m_soundFX;
	std::string m_defaultBullet;

	int m_lives;
	int m_callbackID;
	float m_animSpeed;
};

#endif/* Defined( __LoaderParams__ ) */
