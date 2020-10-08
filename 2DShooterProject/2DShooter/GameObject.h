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

	virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void collision() = 0;
	virtual std::string objType() = 0;

	std::string getTextureID() { return m_textureID; }
	Vector2D& getPosition() { return m_position; }
	Vector2D& getVelocity() { return m_velocity; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	bool isItOn() { return m_bIsOn; }
	bool updating() { return m_bUpdating; }
	bool isInView() { return m_bInView; }
	bool dead() { return m_bDead; }
	bool dying() { return m_bDying; }
	bool& isColliding() { return m_bColliding; }

	void turnObjOn();
	void turnObjOff();


	void setUpdating(bool updating) { m_bUpdating = updating; }
	
	void scroll(float scrollSpeed) 
	{ 
		if (objType() != std::string("Player")) // player is never scrolled
		{
			m_position.setX(m_position.getX() - scrollSpeed);
		}
	}

protected:

	void InViewCheck();

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
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

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