#include "Ohumein_Conga.h"
#include "Debug.h"
#include "Bullet.h"
#include <stdlib.h> 
COhumein_Conga::COhumein_Conga(float x, float y) :CGameObject(x, y)
{
	this->distance_moved = rand() % (MOVING_RANGE / 2);
	this->ax = 0;
	this->ay = OHUMEIN_CONGA_GRAVITY;
	die_start = -1;
	vx = OHUMEIN_CONGA_WALKING_SPEED;
	SetState(OHUMEIN_CONGA_STATE_WALKING);
}

void COhumein_Conga::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - OHUMEIN_CONGA_BBOX_WIDTH / 2;
	top = y - OHUMEIN_CONGA_BBOX_HEIGHT / 2;
	right = left + OHUMEIN_CONGA_BBOX_WIDTH;
	bottom = top + OHUMEIN_CONGA_BBOX_HEIGHT;
}

void COhumein_Conga::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void COhumein_Conga::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == OHUMEIN_CONGA_STATE_DIE) return;
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<COhumein_Conga*>(e->obj)) return;
	if (dynamic_cast<Bullet*>(e->obj)) {
		SetState(OHUMEIN_CONGA_STATE_DIE);
		return;
	}


	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (e->nx > 0) dir = 1;
		else dir = 1 - 1;
		if (state != OHUMEIN_CONGA_STATE_ATTACK && !just_attacked)
			SetState(OHUMEIN_CONGA_STATE_ATTACK);
	}
}

void COhumein_Conga::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	distance_moved += vx * dt;
	if (abs(distance_moved) > MOVING_RANGE)
		vx = -vx, distance_moved = 0, just_attacked = false;
	//DebugOut(L"distance = %f\n", distance_moved);
	if ((state == OHUMEIN_CONGA_STATE_DIE) && (GetTickCount64() - die_start > OHUMEIN_CONGA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if ((state == OHUMEIN_CONGA_STATE_ATTACK) && (GetTickCount64() - attack_start > OHUMEIN_CONGA_ATTACK_TIMEOUT))
	{
		SetState(OHUMEIN_CONGA_STATE_WALKING);
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void COhumein_Conga::Render()
{
	int aniId = ID_ANI_OHUMEIN_CONGA_WALKING;
	if (state == OHUMEIN_CONGA_STATE_DIE)
	{
		aniId = ID_ANI_OHUMEIN_CONGA_DIE;
	}
	else if (state == OHUMEIN_CONGA_STATE_ATTACK)
	{
		aniId = ID_ANI_OHUMEIN_CONGA_ATTACK;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();
}

void COhumein_Conga::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case OHUMEIN_CONGA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case OHUMEIN_CONGA_STATE_WALKING:
		vx = OHUMEIN_CONGA_WALKING_SPEED * dir;
		break;
	case OHUMEIN_CONGA_STATE_ATTACK:
		vx = 0;
		distance_moved = 0;
		just_attacked = true;
		attack_start = GetTickCount64();
	}
}
