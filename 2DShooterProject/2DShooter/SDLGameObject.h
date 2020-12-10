#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include <iostream>

class SDLGameObject : public GameObject
{
public:
	virtual ~SDLGameObject() {}

	virtual void load(const LoaderParams& rParams);
	virtual void reset(const LoaderParams& rParams, Vector2Df* position);
	virtual void draw();
	virtual void update();
	virtual void outOfView();
	virtual void inView();
	virtual void clean() {} //not implemented in this class
	virtual void collision() {} //not implemented in this class
	virtual void collisionPassive() {} //not implemented in this class
	virtual void collisionWithLayer() {} //not implemented in this class

	virtual void addAnimation(std::string& animationID) { m_animations.push_back(animationID); }


	virtual std::string objType() { return "SDLGameObject"; }

protected:
	enum anim_direction { REWIND = -1, PAUSE, FORWARD };
	enum anim_position { BEGIN = -1, MIDDLE, END };

	anim_position m_tbAnimationState;

	SDLGameObject();

	void refreshTextureVariables();

	//returns true when finished, if end frame not entered, will play whole animation
	bool playAnimation(int startFrame, int endFrame);

	//returns true when is new animation and resets the frametimer
	bool switchAnimation(int animationID, bool resetFrameCount = true);

	void resetAnimation(bool resetFrameCount = true);

	//returns true when ready to move a frame
	//bool moveAnimFrame();
	
	void trackFrameTime();

	virtual void handleAnimation();
	virtual void handleDying();

	int m_bulletFiringSpeed;
	int m_bulletCounter;

	int m_moveSpeed;

	int m_dyingTime;
	int m_dyingCounter;

	bool m_bPlayedDeathSound;

	std::vector<std::string> m_animations;
};

#endif /* defined( __SDLGameObject__ ) */