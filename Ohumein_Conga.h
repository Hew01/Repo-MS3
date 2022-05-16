#pragma once
#include "GameObject.h"

#define OHUMEIN_CONGA_GRAVITY 0.002f
#define OHUMEIN_CONGA_WALKING_SPEED 0.05f


#define OHUMEIN_CONGA_BBOX_WIDTH 104
#define OHUMEIN_CONGA_BBOX_HEIGHT 81
#define OHUMEIN_CONGA_BBOX_HEIGHT_DIE 82

#define OHUMEIN_CONGA_DIE_TIMEOUT 8000
#define OHUMEIN_CONGA_ATTACK_TIMEOUT 1500

#define OHUMEIN_CONGA_STATE_IDLE 10
#define OHUMEIN_CONGA_STATE_WALKING 100
#define OHUMEIN_CONGA_STATE_TURNING 200
#define OHUMEIN_CONGA_STATE_ATTACK 300
#define OHUMEIN_CONGA_STATE_ATTACK_FAR 400
#define OHUMEIN_CONGA_STATE_DIE 500

#define ID_ANI_OHUMEIN_CONGA_IDLE 1000201
#define ID_ANI_OHUMEIN_CONGA_WALKING 1000202
#define ID_ANI_OHUMEIN_CONGA_TURNING 1000204
#define ID_ANI_OHUMEIN_CONGA_ATTACK 1000205
#define ID_ANI_OHUMEIN_CONGA_ATTACK_FAR 1000206
#define ID_ANI_OHUMEIN_CONGA_DIE 1000208

#define MOVING_RANGE 70

class COhumein_Conga : public CGameObject
{
	float ax;
	float ay;
	float distance_moved;
	float dir = -1;
	bool just_attacked = false;
	ULONGLONG die_start;
	ULONGLONG attack_start;

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual int IsCollidable() { return 1; };
	virtual int IsBlocking() { return 0; }
	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e);

public:
	COhumein_Conga(float x, float y);
	virtual void SetState(int state);
};