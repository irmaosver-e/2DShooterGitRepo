#ifndef __LoaderParams__
#define __LoaderParams__

#include <iostream>
#include <map>

#include "Vector2D.h"

class LoaderParams
{
public:
	LoaderParams() :
		m_textureID("none"),
		m_numFrames(1),
		m_lives(1),
		m_callbackID(0),
		m_animSpeed(1),
		m_soundFX("none"),
		m_dimentions(Dimention2Di()),
		m_initialPos(Vector2Df()),
		m_anchorPoint(Vector2Df()) {}

	LoaderParams(float x, float y, int width, int height, float anchorX, float anchorY, int numFrames, int lives, int callbackID, float animSpeed, std::string textureID, std::string soundFX) :
		m_textureID(textureID),
		m_numFrames(numFrames),
		m_lives(lives),
		m_callbackID(callbackID),
		m_animSpeed(animSpeed),
		m_soundFX(soundFX),
		m_initialPos(Vector2Df(x, y)),
		m_anchorPoint(Vector2Df(anchorX, anchorY)),
		m_dimentions(Dimention2Di(width, height)) {}


	float getX() const { return m_initialPos.getX(); }
 	float getY() const { return m_initialPos.getY(); }
	int getWidth() const { return m_dimentions.getWidth(); }
	int getHeight() const { return m_dimentions.getHeight(); }
	int getNumFrames() const { return m_numFrames; }
	float getAnimSpeed() const { return m_animSpeed; }
	int getCallbackID() const { return m_callbackID; }
	int getLives() const { return m_lives; }
	std::string getTextureID() const { return m_textureID; }
	std::string getSFX() const { return m_soundFX; }

	float* getXPtr() { return m_initialPos.getXPtr(); }
	float* getYPtr() { return m_initialPos.getYPtr(); }
	int* getWidthPtr() { return m_dimentions.getWidthPtr(); }
	int* getHeightPtr() { return m_dimentions.getHeightPtr(); }
	int* getNumFramesPtr() { return &m_numFrames; }
	float* getAnimSpeedPtr() { return &m_animSpeed; }
	int* getCallbackIDPtr() { return &m_callbackID; }
	int* getLivesPtr() { return &m_lives; }

	float& getXRef() { return m_initialPos.getXRef(); }
	float& getYRef() { return m_initialPos.getYRef(); }
	int& getWidthRef() { return m_dimentions.getWidthRef(); }
	int& getHeightRef() { return m_dimentions.getHeightRef(); }
	int& getCallbackIDRef() { return m_callbackID; }
	std::string& getTextureIDRef() { return m_textureID; }
	std::string& getSFXRef() { return m_soundFX; }

	Vector2Df* getInitialPosPtr() { return &m_initialPos; }
	Vector2Df* getAnchorPointPtr() { return &m_anchorPoint; }
	Dimention2Di* getDimentionsPtr() { return &m_dimentions; }

private:

	Dimention2Di m_dimentions;
	Vector2Df m_initialPos;
	Vector2Df m_anchorPoint;
	
	int m_numFrames;
	std::string m_textureID;
	std::string m_soundFX;

	int m_lives;
	int m_callbackID;
	float m_animSpeed;
};

#endif/* Defined( __LoaderParams__ ) */
