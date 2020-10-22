#include "HUD.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "SDLSystem.h"

void HUD::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);
}

void HUD::draw()
{
	//SDLGameObject::draw();
	/*
	for (int i = 0; i < m_pPlayer->checkLives(); i++)
	{
		TheTextureManager::Instance().drawTile("lives", 2, 2, i * 30, 0, 32, 32, 0, 0, TheSDLSystem::Instance().getRenderer());
	}
	*/

	//SDLGameObject::draw();
	for (int i = 0; i < 3; i++)
	{
		TheTextureManager::Instance().drawTile("lives", 2, 2, i * 30, 0, 32, 32, 0, 0);

	}

	static int i = 0;


	Vector2Df textPos(50, 50);
	TheTextManager::Instance().writeToScreen("Love You " + std::to_string(i % 1000) +" Czesia", textPos);

	i++;

}

void HUD::update()
{
}

void HUD::clean()
{
	SDLGameObject::clean();
}
