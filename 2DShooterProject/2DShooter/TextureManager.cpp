#include "TextureManager.h"
#include <SDL_image.h>

//Define static instance
TextureManager* TextureManager::s_pInstance = nullptr;

TextureManager* TextureManager::Instance()
{
	if (!s_pInstance)
	{
		s_pInstance = new TextureManager();
	}
	return s_pInstance;
}

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str()); //loads image file to a SDL surface
	if (!pTempSurface)
	{
		std::cout << "couldn't find image" << fileName << " - error: "<< IMG_GetError() << "\n";
		return false;
	}
	
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface); //Converts the surface to a texture
	SDL_FreeSurface(pTempSurface); //clears the SDL surface

	//add texture to map
	if (pTexture)
	{
		m_textureMap[id] = pTexture;
		return true;
	}

	//something went wrong
	return false;
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	
	//Draw the texture
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;


	//set alpha
	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	//Draw the texture
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = margin + (spacing + width) * currentFrame;
	srcRect.y = margin + (spacing + height) * currentRow;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap()
{
	m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}
