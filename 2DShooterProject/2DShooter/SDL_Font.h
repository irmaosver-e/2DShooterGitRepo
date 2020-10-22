#ifndef __SDL_Font__
#define __SDL_Font__

#include <iostream>
#include <map>
#include <SDL_ttf.h>

class SDL_Font
{
public:
	SDL_Font() {}
	SDL_Font(std::string fileName) : m_fileName(fileName) {}


	std::string getfileName() const { return m_fileName; }
	void addFontSize(int size);
	void clearFontSizes();
	
	TTF_Font* getSizedFontPtr(int size);

private:

	std::string m_fileName;
	std::map<int, TTF_Font*> m_sizedFonts;
};

#endif /* defined( __SDL_Font__ ) */