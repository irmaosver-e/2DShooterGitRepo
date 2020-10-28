#include "HUD.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "SDLSystem.h"


void HUD::draw()
{
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
