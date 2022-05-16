#ifndef __TILESET_H__
#define __TILESET_H__

#include <d3dx10.h>
#include <unordered_map>

#include "textures.h"
#include "tinyXML\tinyxml\tinyxml.h"
#include "Game.h"
#include "Utils.h"
class TileSet
{
private:
	int firstgid;

	std::string name;

	//tile width and height
	int tilewidth, tileheight;

	//number of tile
	int tilecount;

	//the number of columns
	int columns;

	//image width and height
	int imagewidth, imageheight;

	LPTEXTURE texture;

	std::unordered_map<int, RECT*> cells;
public:
	TileSet();
	TileSet(TiXmlElement* TMXtileset, std::string Path);
	~TileSet();

	int getFirstgid();

	void Draw(int id, float x, float y);
};

typedef TileSet* LPTILESET;
#endif