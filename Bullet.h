#pragma once
#include "GameObject.h"

#define BULLET_SPEED 0.5f

#define BULLET_BBOX_WIDTH 16
#define BULLET_BBOX_HEIGHT 16

#define ID_ANI_PISTOL_BULLET 130800
#define ID_ANI_MG_BULLET 18000
#define ID_ANI_ROCKET_BULLET 19000

class Bullet : public CGameObject
{
protected:
	float ax;
	float ay;
	int anim;
	int bcounter;
	ULONGLONG start_time;
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void OnNoCollision(DWORD dt);

	virtual void OnCollisionWith(LPCOLLISIONEVENT e); 
	void OnCollisionWithChowmeinConga(LPCOLLISIONEVENT e);

public:
	Bullet(float x, float y, float dir, int animation, int ncounter);
};

