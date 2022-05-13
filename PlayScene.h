#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include "Marco.h"
#include "Map.h"
#include "TiledMap.h"
#include "Camera.h"



class CPlayScene : public CScene
{
protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	CBackground* background;
	CForeground* foreground;

	vector<LPGAMEOBJECT> objects;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);

	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_GRID(string line);

	void LoadAssets(LPCWSTR assetFile);
	CMap* tiledMap;
	CCamera* cam;


public:
	CPlayScene(int id, LPCWSTR filePath);
	bool initGridFlag = true;

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() { return player; }

	void Clear();
	void PurgeDeletedObjects();
	void AddObject(CGameObject* obj) { objects.push_back(obj); }


	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

