#ifndef __Tileset__
#define __Tileset__

#include <string>
#include <vector>
#include <map>
#include <SDL_rect.h>

struct Animation
{
	std::string sourceTileSet;
	int sourceColumns;
	int sourceRows;

	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;

	int frameDuration;
	std::vector<int> tileIDs;

};

struct ObjectTile
{
	std::string type;

	std::vector<SDL_Rect> collisionShape;
	Animation animation;
};

struct Tileset
{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int sourceWidth;
	int sourceHeight;
	int numColumns;
	int tileCount;
	std::string name;
	std::map<std::string, ObjectTile> objTileMap;
};

#endif /* defined ( __Tileset__ ) */
