#include "Flying_Killer.h"
#include "Marco.h"
#include "Game.h"

CFlying_Killer::CFlying_Killer(CGameObject* m, float x, float y) :CGameObject(x, y)
{
	player = m;
	this->ax = 0;
	this->ay = FLYING_KILLER_GRAVITY;
	this->isDisplay = true;
	this->isEnable = true;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);
	if (posX < SCREEN_WIDTH / 2) {
		this->minX = 0;
		this->maxX = SCREEN_WIDTH;
	}
	else {
		this->minX = posX - SCREEN_WIDTH / 2;
		this->maxX = posX + SCREEN_WIDTH / 2;
	}
	die_start = -1;
	SetState(FLYING_KILLER_STATE_JUMPING);
}

void CFlying_Killer::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FLYING_KILLER_BBOX_WIDTH / 2;
	top = y - FLYING_KILLER_BBOX_HEIGHT / 2;
	right = left + FLYING_KILLER_BBOX_WIDTH;
	bottom = top + FLYING_KILLER_BBOX_HEIGHT;
}

void CFlying_Killer::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CFlying_Killer::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFlying_Killer*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CFlying_Killer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);

	if ((state == FLYING_KILLER_STATE_JUMPING) && (x > maxX || x < minX)) {
		vx = -vx;
	}
	if ((state == FLYING_KILLER_STATE_DIE) && (GetTickCount64() - die_start > FLYING_KILLER_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CFlying_Killer::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_FLYING_KILLER_JUMPING;
	switch (state)
	{
	case FLYING_KILLER_STATE_DIE:
		aniId = ID_ANI_FLYING_KILLER_DIE;
		break;
	case FLYING_KILLER_STATE_ATTACK:
		aniId = ID_ANI_FLYING_KILLER_ATTACK;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();
}

void CFlying_Killer::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FLYING_KILLER_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		isDisplay = false;
		isEnable = false;
		break;
	case FLYING_KILLER_STATE_JUMPING:
		vx = -FLYING_KILLER_WALKING_SPEED;
		break;
	case FLYING_KILLER_STATE_ATTACK:
		break;
	}
}
