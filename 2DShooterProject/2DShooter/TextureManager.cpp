#include "TextureManager.h"
#include <SDL_image.h>
#include "SDLSystem.h"

bool TextureManager::loadTextureFromFile(std::string fileName, std::string id)
{
	//checks if the texture already exists
	if (m_textureMap.find(id) == m_textureMap.end())
	{
		SDL_Surface* pTempSurface = IMG_Load(fileName.c_str()); //loads image file to a SDL surface
		if (!pTempSurface)
		{
			std::cout << "in TextureManager::load \n";
			std::cout << "couldn't find image " << fileName << " - error: " << IMG_GetError() << "\n";
			return false;
		}

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheSDLSystem::Instance().getRenderer(), pTempSurface); //Converts the surface to a texture
		SDL_FreeSurface(pTempSurface); //clears the SDL surface

		//add texture to map
		if (pTexture)
		{
			m_textureMap[id] = pTexture;
			return true;
		}
	}

	//something went wrong or the texture is duplicate
	return false;
}

void TextureManager::drawFromSurface(SDL_Surface* pSurface, Vector2Df& position, int width, int height, SDL_RendererFlip flip)
{
	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(TheSDLSystem::Instance().getRenderer(), pSurface);
	SDL_FreeSurface(pSurface);
	
	drawFromTexture(pTexture, position, width, height, flip);
	SDL_DestroyTexture(pTexture);
}

void TextureManager::draw(std::string id, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	Vector2Df position(x, y);
	drawFromTexture(m_textureMap[id], position , width, height, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, double angle, int alpha, SDL_RendererFlip flip)
{
	SDL_Rect m_srcRect;
	SDL_Rect m_destRect;

	m_srcRect.x = width * currentFrame;
	m_srcRect.y = height * currentRow;
	m_srcRect.w = m_destRect.w = width;
	m_srcRect.h = m_destRect.h = height;
	m_destRect.x = x;
	m_destRect.y = y;


	//set alpha
	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	//Draw the texture
	SDL_RenderCopyEx(TheSDLSystem::Instance().getRenderer(), m_textureMap[id], &m_srcRect, &m_destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, int alpha)
{
	std::string textureID = id;
	int textureColumn = currentFrame;
	int textureRow = currentRow;
	int textureMargin = margin;
	int textureSpacing = spacing;
	int textureWidth = width;
	int textureHeight = height;

	if (m_animationMap.find(id) != m_animationMap.end())
	{
		textureID = m_animationMap[id].sourceTileSet;
		
		textureColumn = m_animationMap[id].tileIDs[currentFrame] % m_animationMap[id].sourceColumns;
		textureRow = m_animationMap[id].tileIDs[currentFrame] / m_animationMap[id].sourceColumns;
		textureMargin = m_animationMap[id].margin;
		textureSpacing = m_animationMap[id].spacing;
		textureWidth = m_animationMap[id].tileWidth;
		textureHeight = m_animationMap[id].tileHeight;
	}

	SDL_Rect m_srcRect;
	SDL_Rect m_destRect;

	m_srcRect.x = textureMargin + (textureSpacing + textureWidth) * textureColumn;
	m_srcRect.y = textureMargin + (textureSpacing + textureHeight) * textureRow;
	m_srcRect.w = m_destRect.w = textureWidth;
	m_srcRect.h = m_destRect.h = textureHeight;
	m_destRect.x = x;
	m_destRect.y = y;

	//set alpha
	SDL_SetTextureAlphaMod(m_textureMap[textureID], alpha);
	SDL_RenderCopyEx(TheSDLSystem::Instance().getRenderer(), m_textureMap[textureID], &m_srcRect, &m_destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::drawFromTexture(SDL_Texture* pTexture, Vector2Df& position, int width, int height, SDL_RendererFlip flip)
{
	//SDL_RenderClear(TheSDLSystem::Instance().getRenderer());

	SDL_Rect m_srcRect;
	SDL_Rect m_destRect;

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = m_destRect.w = width;
	m_srcRect.h = m_destRect.h = height;
	m_destRect.x = position.getX();
	m_destRect.y = position.getY();

	//Draw the texture
	SDL_RenderCopyEx(TheSDLSystem::Instance().getRenderer(), pTexture, &m_srcRect, &m_destRect, 0, 0, flip);
}

void TextureManager::clearTextureMap()
{
	//destroy all textures in the map
	for (std::map<std::string, SDL_Texture*>::iterator it = m_textureMap.begin(); it != m_textureMap.end(); it++)
	{
		SDL_DestroyTexture(it->second);
		it->second = nullptr;
	}
	
	m_textureMap.clear();
}

int TextureManager::getAnimationFrameCount(std::string& animName)
{
	int frameCount = 0;

	if (m_animationMap.find(animName) != m_animationMap.end())
	{
		frameCount = m_animationMap[animName].tileIDs.size();
	}

	return frameCount;
}

/*
//possible implementation
void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}
*/


