#pragma once
#include "GameObject.h"

#define LOCUST_WALKING_SPEED 0.05f;

#define LOCUST_BBOX_WIDTH 51
#define LOCUST_BBOX_HEIGHT 45
#define LOCUST_BBOX_HEIGHT_DIE 52
#define LOCUST_DIE_TIMEOUT 2000
#define LOCUST_TURNING_TIMEOUT 3000
#define LOCUST_EATING_TIMEOUT	2000

#define LOCUST_STATE_IDLE 10
#define LOCUST_STATE_FLYING 100
#define LOCUST_STATE_TURNING 200
#define LOCUST_STATE_PRE_ATTACK 300
#define LOCUST_STATE_ATTACKING 400
#define LOCUST_STATE_CATCH_PLAYER 500
#define LOCUST_STATE_EATING 600
#define LOCUST_STATE_DIE 700

#define LOCUST_ANI_FLYING 0
#define LOCUST_ANI_DIE 1   

#define ID_ANI_LOCUST_FLYING 8801001
#define ID_ANI_LOCUST_TURNING 8801002
#define ID_ANI_LOCUST_PRE_ATTACK 8801003
#define ID_ANI_LOCUST_ATTACKING 8801004
#define ID_ANI_LOCUST_CATCH_PLAYER 8801005
#define ID_ANI_LOCUST_EATING 8801006

#define ID_ANI_LOCUST_CATCH_DIE 8801009

#define LOCUST_GRAVITY 0.002f
#define LOCUST_TURNING_SPEED 0.12f

class CLocust : public CGameObject
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
	CLocust(CGameObject* m, float x, float y);
	virtual void SetState(int state);
};