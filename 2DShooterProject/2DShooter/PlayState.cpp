#include "PlayState.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_PAUSE))
	{
		TheGame::Instance()->getStateMachine()->pushState(new PauseState());
	}

	pLevel->update();

	/*
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->update();
	}

	if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]), dynamic_cast<SDLGameObject*>(m_gameObjects[1])))
	{
		TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
	}
	*/
}

void PlayState::render()
{
	pLevel->render();
	/*
	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
	*/
}

bool PlayState::onEnter()
{
	//parse the state
	//StateParser stateParser;
	//stateParser.parseState("test.xml", s_playID, &m_gameObjects, &m_textureIDList);

	LevelParser levelParser;
	pLevel = levelParser.parseLevel("assets/map1.tmx");

	std::cout << "Entering PlayState \n";

	return true;
}

bool PlayState::onExit()
{
	std::cout << "Exiting play state \n";

	for (unsigned int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		TheTextureManager::Instance()->clearFromTextureMap(dynamic_cast<SDLGameObject*>(m_gameObjects[i])->getTextureID());
	}

	m_gameObjects.clear();

	//clear the texture manager
	for (unsigned int i = 0; i < m_textureIDList.size(); i++)
	{
		TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
	}

	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;
	
	//rect A
	leftA = (int)p1->getPosition().getX();
	topA = (int)p1->getPosition().getY();
	rightA = (int)(p1->getPosition().getX() + p1->getWidth());
	bottomA = (int)(p1->getPosition().getY() + p1->getHeight());

	//rect B
	leftB = (int)p2->getPosition().getX();
	topB = (int)p2->getPosition().getY();
	rightB = (int)(p2->getPosition().getX() + p2->getWidth());
	bottomB = (int)(p2->getPosition().getY() + p2->getHeight());

	//checks if any sides are outside of rect B
	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}

