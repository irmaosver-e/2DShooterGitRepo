#include "SDL_Font.h"

void SDL_Font::addFontSize(int size)
{
	//checks if font size already exists, if not add
	if(m_sizedFonts.find(size) == m_sizedFonts.end())
	{  
		m_sizedFonts[size] = TTF_OpenFont(m_fileName.c_str(), size);
	}
}

void SDL_Font::clearFontSizes()
{
	//Close the fonts stored
	for (std::map<int, TTF_Font*>::iterator itSizedFont = m_sizedFonts.begin(); itSizedFont != m_sizedFonts.end(); ++itSizedFont)
	{
		TTF_CloseFont(itSizedFont->second);
	}

	m_sizedFonts.clear();
}

TTF_Font* SDL_Font::getSizedFontPtr(int size)
{
	//checks if font size exists, if yes return it
	if (m_sizedFonts.find(size) != m_sizedFonts.end())
	{
		return m_sizedFonts[size];
	}
	else
	{
		std::cout << "no font of size " << size << " loaded for " << m_fileName << "\n";
	}
	return nullptr;
}
