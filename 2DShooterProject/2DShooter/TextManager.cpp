#include "TextManager.h"
#include "TextureManager.h"


bool TextManager::init()
{
	if (TTF_Init() == -1) 
	{
		std::cout << "TTF_Init: " << TTF_GetError() << "\n";
		return false;
	}
	return true;
}

void TextManager::quit()
{
	//erases the fontTypes created
	for (std::map<std::string, SDL_Font>::iterator itFontType = m_fontTypes.begin(); itFontType != m_fontTypes.end(); ++itFontType)
	{
		itFontType->second.clearFontSizes();
	}
	m_fontTypes.clear();

	//Quit SDL_ttf
	TTF_Quit();
}

bool TextManager::loadFont(const std::string& fontName, int fontSize, const std::string& fileName)
{
	bool loadedFont = true;

	//checks if its a new type
	if (m_fontTypes.find(fontName) == m_fontTypes.end())
	{
		//checks if a filename was passed
		if (fileName != "")
		{
			SDL_Font fontType(m_fontRepositoryPath + fileName);
			fontType.addFontSize(fontSize);
			m_fontTypes[fontName] = fontType;
		}
		else
		{
			std::cout << "fileName not provided for font " << fontName << "\n";
			loadedFont = false;
		}
	}
	else
	{ // the Type already exist, it must be a new size
		m_fontTypes[fontName].addFontSize(fontSize);
	}

	//sets the current font to the loaded font
	m_currentFont = m_fontTypes[fontName].getSizedFontPtr(fontSize);

	return loadedFont;
}

bool TextManager::useFont(const std::string& fontName, int fontSize)
{
	//checks if the type exists
	if (m_fontTypes.find(fontName) != m_fontTypes.end())
	{
		//checks if the size exists
		if (m_fontTypes[fontName].getSizedFontPtr(fontSize))
		{
			m_currentFont = m_fontTypes[fontName].getSizedFontPtr(fontSize);
			return true;
		}
		else
		{
			if (loadFont(fontName, fontSize))
			{
				useFont(fontName, fontSize);
			}
			else
			{
				std::cout << "font " << fontName << " does NOT have size " << fontSize << " and failed to load new size\n";
			}
		}
	}
	else
	{
		std::cout << "no font of type " << fontName  << "\n";
	}

	return false;
}

void TextManager::writeToScreen(const std::string& message, Vector2Df& position, SDL_Color txtColour)
{
	//SDL_Surface* pMsgSurface = TTF_RenderText_Solid(m_currentFont, message.c_str(), txtColour);
	SDL_Surface* pMsgSurface = TTF_RenderText_Blended(m_currentFont, message.c_str(), txtColour);
	
	//Draw the text
	TheTextureManager::Instance().drawFromSurface(pMsgSurface, position, pMsgSurface->w, pMsgSurface->h);

	//surface freed in drawFromSurface()
}
