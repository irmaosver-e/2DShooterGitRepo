#ifndef __GameObject__
#define __GameObject__

#include <iostream>

#include "LoaderParams.h"
#include "Vector2D.h"

#include <vector>
#include <SDL_rect.h>

class GameObject
{
public:
	virtual ~GameObject() {}

	//virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;
	virtual void load(const LoaderParams& rParams) = 0;
	virtual void reset(const LoaderParams& rParams) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void collision() = 0;
	virtual void collisionPassive() = 0;
	virtual void collisionWithLayer() = 0;
	virtual void outOfView() = 0;
	virtual void inView() = 0;
	virtual std::string objType() = 0;

	std::string getTextureID() { return m_textureID; }
	Vector2Df& getPosition() { return m_position; }
	Vector2Df& getVelocity() { return m_velocity; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	bool isOn() { return m_bIsOn; }
	bool isInView() { return m_bInView; }
	bool updating() { return m_bUpdating; }
	bool dead() { return m_bDead; }
	bool dying() { return m_bDying; }
	bool& isColliding() { return m_bColliding; }

	void inViewCheck();	

	void turnObjOn();
	void turnObjOff();

	void setUpdating(bool updating) { m_bUpdating = updating; }
	void setInView(bool inView) { m_bInView = inView; }
	
	virtual void scroll(float scrollSpeed);

protected:

	// constructor with default initialisation list
	GameObject() : m_position(0, 0),
		m_velocity(0, 0),
		m_acceleration(0, 0),
		m_width(0),
		m_height(0),
		m_currentRow(0),
		m_currentFrame(0),
		m_bIsOn(false),
		m_bInView(false),
		m_bUpdating(false),
		m_bColliding(false),
		m_bDead(false),
		m_bDying(false),
		m_angle(0),
		m_alpha(255),
		m_sfx("")
	{
	}

	//movement variables
	Vector2Df m_position;
	Vector2Df m_velocity;
	Vector2Df m_acceleration;

	//size variables
	int m_width;
	int m_height;

	//animation variables
	int m_currentRow;
	int m_currentFrame;
	int m_numFrames;
	int m_animSpeed;
	std::string m_textureID;

	//common boolean variables
	bool m_bIsOn;
	bool m_bInView;
	bool m_bUpdating;
	bool m_bColliding;
	bool m_bDead;
	bool m_bDying;

	//rotation
	double m_angle;

	//alpha
	int m_alpha;

	//soundFXs
	std::string m_sfx;

};

#endif  /* defined( __GameObjectr__) */