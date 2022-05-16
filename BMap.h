#ifndef __BMAP_H__
#define __BMAP_H__

#include <vector>
#include <d3dx10.h>

#include "Utils.h"
#include "Layer.h"
#include "TileSet.h"
#include "tinyXML/tinyxml/tinyxml.h"
#include "GameObject.h"
#include "Game.h"
#include "debug.h"
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
class BMap
{

	//the cell count of the BMap
	int width, height;
	//the cell's width and height
	int tilewidth, tileheight;

	LPTILESET tilesets;

	std::vector<LPLAYER> layers;
public:
	BMap();
	~BMap();

	void AddTileSet(LPTILESET tileset);
	void AddLayer(LPLAYER layer);

	//FilePath is path to the file itself , Path = Path to storage area
	void LoadBMapfromTMX(const char* FilePath, const char* Path);

	void Update(DWORD dt);
	void Render();

	void Unload();

	float getBMapHeight();
	float getBMapWidth();

	LPTILESET GetTilesetbyTileID(int ID);
};

#endif