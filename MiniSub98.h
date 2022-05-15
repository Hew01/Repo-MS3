#pragma once
#include "GameObject.h"

#define MINISUB_WALKING_SPEED 0.05f;

#define MINISUB_BBOX_WIDTH 51
#define MINISUB_BBOX_HEIGHT 45
#define MINISUB_BBOX_HEIGHT_DIE 52
#define MINISUB_DIE_TIMEOUT 2000


#define MINISUB_STATE_SWINMING 10
#define MINISUB_STATE_TURNING 100
#define MINISUB_STATE_TORPEDOES 200
#define MINISUB_STATE_EFECT 300
#define MINISUB_STATE_GET_HIT 400
#define MINISUB_STATE_FALLING_APART 500
#define MINISUB_STATE_DEBIRS 600



#define MINISUB_ANI_FLYING 0
#define MINISUB_ANI_DIE 1   

#define ID_ANI_MINISUB_SWIMING 9000632
#define ID_ANI_MINISUB_TURNING 9000633
#define ID_ANI_MINISUB_TORPEDOES 9000634
#define ID_ANI_MINISUB_EFECT 9000635
#define ID_ANI_MINISUB_GET_HIT 9000636
#define ID_ANI_MINISUB_FALLING_APART 9000637
#define ID_ANI_MINISUB_DEBIRS 9000638


#define MINISUB_GRAVITY 0.002f
#define MINISUB_TURNING_SPEED 0.12f

class CMiniSub98 : public CGameObject
{
	CGameObject* player;
	DWORD time_moving;
	int type;

	float ax;
	float ay;

	bool isDisplay;
	bool isEnable;

	float maxX;
	float minX;

	ULONGLONG die_start;
	ULONGLONG start_turning;
	ULONGLONG start_eating;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	CMiniSub98(CGameObject* m, float x, float y);
	virtual void SetState(int state);
};