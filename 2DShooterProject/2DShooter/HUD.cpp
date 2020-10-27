#include "HUD.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "SDLSystem.h"

/*
void HUD::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);
}

*/

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

	//  implementation in progress
	for (GameObject* animGrafic : m_animGraphics)
	{
		animGrafic->draw();
	}

	for (GameObject* textBox : m_textBoxes)
	{
		textBox->draw();
	}

}

void HUD::update()
{
}

void HUD::clean()
{
	SDLGameObject::clean();
}
