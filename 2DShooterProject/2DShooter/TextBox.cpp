#include <string>
#include "TextBox.h"

#include "TextManager.h"

void TextBox::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);
	m_textColour = rParams.getColour();
	m_fontType = rParams.getFontType();
	m_text = rParams.getTextBoxMessage();
}

void TextBox::draw()
{
	static int i = 0;

	TheTextManager::Instance().writeToScreen(m_text + std::to_string(i % 1000), m_position, m_textColour.m_colours);

	i++;
}
