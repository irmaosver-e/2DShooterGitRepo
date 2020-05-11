#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"

#include <iostream>

#include "TextureManager.h"
#include "Game.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "Level.h"

#include "Player.h"
#include "Enemy.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

	virtual std::string getStateID() const { return s_playID; }

private:
	static const std::string s_playID;

	std::vector<GameObject*> m_gameObjects;

	Level* pLevel;
};

#endif /* defined ( __PlayState__ ) */
