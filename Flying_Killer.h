#pragma once
#include "GameObject.h"

#define FLYING_KILLER_GRAVITY 0.002f
#define FLYING_KILLER_WALKING_SPEED 0.05f


#define FLYING_KILLER_BBOX_WIDTH 29
#define FLYING_KILLER_BBOX_HEIGHT 36
#define FLYING_KILLER_BBOX_HEIGHT_DIE 33

#define FLYING_KILLER_DIE_TIMEOUT 8000

#define FLYING_KILLER_STATE_JUMPING	12
#define FLYING_KILLER_STATE_ATTACK 100
#define FLYING_KILLER_STATE_DIE 200

#define ID_ANI_FLYING_KILLER_JUMPING 1000801
#define ID_ANI_FLYING_KILLER_ATTACK 1000802
#define ID_ANI_FLYING_KILLER_DIE 1000803


class CFlying_Killer : public CGameObject
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
	CFlying_Killer(CGameObject* m, float x, float y);
	virtual void SetState(int state);
};