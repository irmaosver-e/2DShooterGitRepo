#ifndef __LoaderParams__
#define __LoaderParams__

#include <iostream>
#include <map>
#include <SDL_pixels.h>

#include "Vector2D.h"

struct Colour
{
	Colour(Uint8 cRed = 255, Uint8 cGreen = 255, Uint8 cBlue= 255, Uint8 cAlpha = 255)
	{
		m_colours.r = cRed;
		m_colours.g = cGreen;
		m_colours.b = cBlue;
		m_colours.a = cAlpha;
	}

	void operator=(const Colour& c)
	{
		m_colours.r = c.m_colours.r;
		m_colours.g = c.m_colours.g;
		m_colours.b = c.m_colours.b;
		m_colours.a = c.m_colours.a;
	}

	SDL_Colour m_colours;

};

class LoaderParams
{
public:
	LoaderParams() :
		m_colour(Colour()),
		m_subTypeID("none"),
		m_textureID("none"),
		m_numFrames(1),
		m_lives(1),
		m_callbackID(0),
		m_animSpeed(1),
		m_soundFX("none"),
		m_textBoxMessage(""),
		m_dimentions(Dimention2Di()),
		m_initialPos(Vector2Df()),
		m_anchorPoint(Vector2Df()) 
	{
		m_valueToWatch = nullptr;
	}

	
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
	int getFontSize() const { return m_fontSize; }
	std::string getSubTypeID() const { return m_subTypeID; }
	std::string getSFX() const { return m_soundFX; }
	std::string getFontType() const { return m_fontType; }
	std::string getTextBoxMessage() const { return m_textBoxMessage; }
	Colour getColour() const { return m_colour; }

	float* getXPtr() { return m_initialPos.getXPtr(); }
	float* getYPtr() { return m_initialPos.getYPtr(); }
	int* getWidthPtr() { return m_dimentions.getWidthPtr(); }
	int* getHeightPtr() { return m_dimentions.getHeightPtr(); }
	int* getNumFramesPtr() { return &m_numFrames; }
	float* getAnimSpeedPtr() { return &m_animSpeed; }
	int* getCallbackIDPtr() { return &m_callbackID; }
	int* getLivesPtr() { return &m_lives; }
	int* getFontSizePtr() { return &m_fontSize; }
	Vector2Df* getInitialPosPtr() { return &m_initialPos; }
	Vector2Df* getAnchorPointPtr() { return &m_anchorPoint; }
	Dimention2Di* getDimentionsPtr() { return &m_dimentions; }
	Colour* getColourPtr() { return &m_colour; }

	void setValueToWatchPtr(int* pValue) { m_valueToWatch = pValue; }
	int* getValueToWatchPtr() const{ return m_valueToWatch; }

	float& getXRef() { return m_initialPos.getXRef(); }
	float& getYRef() { return m_initialPos.getYRef(); }
	int& getWidthRef() { return m_dimentions.getWidthRef(); }
	int& getHeightRef() { return m_dimentions.getHeightRef(); }
	int& getCallbackIDRef() { return m_callbackID; }
	int& getFontSizeRef() { return m_fontSize; }
	std::string& getSubTypeIDRef() { return m_subTypeID; }
	std::string& getSFXRef() { return m_soundFX; }
	std::string& getFontTypeRef() { return m_fontType; }
	std::string& getTextBoxMessageRef() { return m_textBoxMessage; }
	Colour& getColourRef() { return m_colour; }

private:

	Colour m_colour;

	Dimention2Di m_dimentions;
	Vector2Df m_initialPos;
	Vector2Df m_anchorPoint;
	
	std::string m_subTypeID;
	std::string m_soundFX;
	std::string m_fontType;
	std::string m_textBoxMessage;

	int m_numFrames;
	int m_fontSize;
	int m_lives;
	int m_callbackID;
	float m_animSpeed;

	int* m_valueToWatch;

	//should be a vector of animations
	std::string m_textureID;
};

#endif/* Defined( __LoaderParams__ ) */
