#include "Chowmein_Conga.h"
#include "Debug.h"
#include "Bullet.h"
#include <stdlib.h> 
Chowmein_Conga::Chowmein_Conga(float x, float y) :CGameObject(x, y)
{
	this->distance_moved = rand()%(MOVING_RANGE/2);
	this->ax = 0;
	this->ay = CHOWMEIN_CONGA_GRAVITY;
	die_start = -1;
	vx = CHOWMEIN_CONGA_WALKING_SPEED;
	SetState(CHOWMEIN_CONGA_STATE_WALKING);
}

void Chowmein_Conga::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - CHOWMEIN_CONGA_BBOX_WIDTH / 2;
	top = y - CHOWMEIN_CONGA_BBOX_HEIGHT / 2;
	right = left + CHOWMEIN_CONGA_BBOX_WIDTH;
	bottom = top + CHOWMEIN_CONGA_BBOX_HEIGHT;
}

void Chowmein_Conga::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Chowmein_Conga::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (state == CHOWMEIN_CONGA_STATE_DIE) return;
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<Chowmein_Conga*>(e->obj)) return;
	if (dynamic_cast<Bullet*>(e->obj)) {
		SetState(CHOWMEIN_CONGA_STATE_DIE);
		return;
	}


	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		if (e->nx > 0) dir=1;
		else dir = 1-1;
		if (state!=CHOWMEIN_CONGA_STATE_ATTACK && !just_attacked)
			SetState(CHOWMEIN_CONGA_STATE_ATTACK);
	}
}

void Chowmein_Conga::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	distance_moved += vx * dt;
	if (abs(distance_moved) > MOVING_RANGE)
		vx = -vx, distance_moved = 0, just_attacked =false;
	//DebugOut(L"distance = %f\n", distance_moved);
	if ((state == CHOWMEIN_CONGA_STATE_DIE) && (GetTickCount64() - die_start > CHOWMEIN_CONGA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}	
	if ((state == CHOWMEIN_CONGA_STATE_ATTACK) && (GetTickCount64() - attack_start > CHOWMEIN_CONGA_ATTACK_TIMEOUT))
	{
		SetState(CHOWMEIN_CONGA_STATE_WALKING);
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void Chowmein_Conga::Render()
{
	int aniId = ID_ANI_CHOWMEIN_CONGA_WALKING;
	if (state == CHOWMEIN_CONGA_STATE_DIE)
	{
		aniId = ID_ANI_CHOWMEIN_CONGA_DIE;
	}
	else if (state == CHOWMEIN_CONGA_STATE_ATTACK)
	{
		aniId = ID_ANI_CHOWMEIN_CONGA_ATTACK;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();
}

void Chowmein_Conga::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case CHOWMEIN_CONGA_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case CHOWMEIN_CONGA_STATE_WALKING:
		vx = CHOWMEIN_CONGA_WALKING_SPEED*dir;
		break;
	case CHOWMEIN_CONGA_STATE_ATTACK:
		vx = 0;
		distance_moved = 0;
		just_attacked = true;
		attack_start = GetTickCount64();
	}
}
