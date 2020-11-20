#ifndef __TextManager__
#define __TextManager__

#include "Singleton.h"
#include "SDL_Font.h"
#include "Vector2D.h"

class TextManager : public Singleton<TextManager>
{
public:
	TextManager(token) {}
	~TextManager() {}

	bool init();
	void quit();

	bool loadFont(const std::string& fontName, int fontSize, const std::string& fileName = "");
	bool useFont(const std::string& fontName, int fontSize);

	void writeToScreen(const std::string& message, Vector2Df& position, SDL_Color txtColour = {255, 255, 255});
	
	void setFontRepositoryPath(const std::string& path) { m_fontRepositoryPath = path; }

private:
	std::string m_fontRepositoryPath;

	TTF_Font* m_currentFont;
	std::map<std::string, SDL_Font> m_fontTypes;
};

typedef TextManager TheTextManager;

#endif /* defined(__TextureManager__) */