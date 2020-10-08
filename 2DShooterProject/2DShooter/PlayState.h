#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include "CollisionManager.h"
#include "Level.h"

#include "GameObject.h"

class PlayState : public GameState
{
public:
	virtual ~PlayState() { delete m_pLevel; }

	virtual bool update();
	virtual bool render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;

};

#endif /* defined ( __PlayState__ ) */
