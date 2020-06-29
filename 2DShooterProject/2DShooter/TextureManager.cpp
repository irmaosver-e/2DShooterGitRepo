#include "TextureManager.h"
#include <SDL_image.h>

bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str()); //loads image file to a SDL surface
	if (!pTempSurface)
	{
		std::cout << "in TextureManager::load \n";
		std::cout << "couldn't find image " << fileName << " - error: "<< IMG_GetError() << "\n";
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
	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = m_destRect.w = width;
	m_srcRect.h = m_destRect.h = height;
	m_destRect.x = x;
	m_destRect.y = y;
	
	//Draw the texture
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &m_srcRect, &m_destRect, 0, 0, flip);
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, double angle, int alpha, SDL_RendererFlip flip)
{
	m_srcRect.x = width * currentFrame;
	m_srcRect.y = height * currentRow;
	m_srcRect.w = m_destRect.w = width;
	m_srcRect.h = m_destRect.h = height;
	m_destRect.x = x;
	m_destRect.y = y;


	//set alpha
	SDL_SetTextureAlphaMod(m_textureMap[id], alpha);
	//Draw the texture
	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &m_srcRect, &m_destRect, angle, 0, flip);
}

void TextureManager::drawTile(std::string id, int margin, int spacing, int x, int y, int width, int height, int currentRow, int currentFrame, SDL_Renderer* pRenderer)
{
	std::string textureID = id;
	int textureColumn = currentFrame;
	int textureRow = currentRow;

	if (m_animationMap.find(id) != m_animationMap.end())
	{
		textureID = m_animationMap[id].sourceTileSet;
		
		textureColumn = m_animationMap[id].tileIDs[currentFrame] % m_animationMap[id].sourceColumns;
		textureRow = m_animationMap[id].tileIDs[currentFrame] / m_animationMap[id].sourceColumns;

	}

	m_srcRect.x = margin + (spacing + width) * textureColumn;
	m_srcRect.y = margin + (spacing + height) * textureRow;
	m_srcRect.w = m_destRect.w = width;
	m_srcRect.h = m_destRect.h = height;
	m_destRect.x = x;
	m_destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[textureID], &m_srcRect, &m_destRect, 0, 0, SDL_FLIP_NONE);
}

void TextureManager::clearTextureMap()
{
	m_textureMap.clear();
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}
