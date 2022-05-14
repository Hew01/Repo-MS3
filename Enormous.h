#pragma once
class enormous
{
};

#pragma once
#include "GameObject.h"

#define ENORMOUS_WALKING_SPEED 0.05f;

#define ENORMOUS_BBOX_WIDTH 51
#define ENORMOUS_BBOX_HEIGHT 45
#define ENORMOUS_BBOX_HEIGHT_DIE 52
#define ENORMOUS_DIE_TIMEOUT 2000


#define ENORMOUS_STATE_IDLE 10
#define ENORMOUS_STATE_ATTACK 100
#define ENORMOUS_STATE_CRASHING_AGAIN 200
#define ENORMOUS_STATE_RETURN 300

#define ENORMOUS_ANI_FLYING 0
#define ENORMOUS_ANI_DIE 1   

#define ID_ANI_ENORMOUS_IDLE_ATTACK 8900621
#define ID_ANI_ENORMOUS_CRASHING_AGAIN 8900622
#define ID_ANI_ENORMOUS_RETURN 8900623


#define ENORMOUS_GRAVITY 0.002f
#define ENORMOUS_TURNING_SPEED 0.12f

class CEnormous : public CGameObject
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
	CEnormous(CGameObject* m, float x, float y);
	virtual void SetState(int state);
};