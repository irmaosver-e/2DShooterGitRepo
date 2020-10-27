#include <string>
#include "TextBox.h"

#include "TextManager.h"

void TextBox::load(const LoaderParams& rParams)
{
	SDLGameObject::load(rParams);
	m_textColour = rParams.getColour();
	m_fontType = rParams.getFontType();
	m_text = rParams.getTextBoxMessage();
	m_fontSize = rParams.getFontSize();
	m_watchedValue = rParams.getValueToWatchPtr();
}

void TextBox::draw()
{
	
	TheTextManager::Instance().useFont(m_fontType, m_fontSize);
	TheTextManager::Instance().writeToScreen(textAndValueMessage(), m_position, m_textColour.m_colours);

}

std::string TextBox::textAndValueMessage()
{
	std::string search = "(#)";

	std::string replace = "";
	if (m_watchedValue)
	{
		replace = std::to_string(*m_watchedValue);
	}
	
	std::string resultMessage = m_text;

	// plugs in value to message
	int pos = 0;
	while ((pos = resultMessage.find(search, pos)) != std::string::npos) {
		resultMessage.replace(pos, search.length(), replace);
		pos += replace.length();
	}

	return resultMessage;
}
