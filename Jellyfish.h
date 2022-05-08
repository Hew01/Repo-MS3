#pragma once
#include "GameObject.h"

#define JELLYFISH_GRAVITY 0.002f
#define JELLYFISH_WALKING_SPEED 0.05f


#define JELLYFISH_BBOX_WIDTH 22
#define JELLYFISH_BBOX_HEIGHT 23
#define JELLYFISH_BBOX_HEIGHT_DIE 28

#define JELLYFISH_DIE_TIMEOUT 8000

#define JELLYFISH_STATE_WALKING 100
#define JELLYFISH_STATE_DIE 200

#define ID_ANI_JELLYFISH_WALKING 1001001
#define ID_ANI_JELLYFISH_DIE 1001002

class CJellyfish : public CGameObject
{
	CGameObject* player;
	DWORD time_moving;

	float ax;
	float ay;

	bool isDisplay;
	bool isEnable;

	float maxX;
	float minX;

	ULONGLONG die_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CJellyfish(CGameObject* m, float x, float y);
	virtual void SetState(int state);
};