#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <map>
#include <SDL.h>
#include "Singleton.h"

class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager(token) {}
	~TextureManager() {};

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer *pRenderer);
	
	void clearTextureMap();
	void clearFromTextureMap(std::string id);

	std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }


private:	
	std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

#endif /* defined(__TextureManager__) */
