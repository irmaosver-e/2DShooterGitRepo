#include "HUD.h"
#include "TextureManager.h"
#include "TextManager.h"
#include "SDLSystem.h"


HUD::~HUD()
{
	for (GameObject* animGrafic : m_animGraphics)
	{
		delete animGrafic;
	}

	for (GameObject* textBox : m_textBoxes)
	{
		delete textBox;
	}

	m_animGraphics.clear();
	m_textBoxes.clear();
}

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
