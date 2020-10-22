#ifndef __TextureManager__
#define __TextureManager__

#include <iostream>
#include <map>
#include <SDL.h>
#include "Singleton.h"
#include "Tileset.h"
#include "Vector2D.h"

class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager(token) {}
	~TextureManager() {};

	bool loadTextureFromFile(std::string fileName, std::string id);

	void drawFromSurface(SDL_Surface* pSurface, Vector2Df& position, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, int alpha, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame);

	void clearTextureMap();
	void clearFromTextureMap(std::string id);

	std::map<std::string, Animation>& getAnimationMap() { return m_animationMap; }

	std::map<std::string, SDL_Texture*> getTextureMap() { return m_textureMap; }


private:	
	void drawFromTexture(SDL_Texture* pTexture, Vector2Df& position, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE);

	std::map<std::string, Animation> m_animationMap;
	std::map<std::string, SDL_Texture*> m_textureMap;
};

typedef TextureManager TheTextureManager;

#endif /* defined(__TextureManager__) */
