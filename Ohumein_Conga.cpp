#include "Ohumein_Conga.h"
#include "Marco.h"
#include "Game.h"

COhumein_Conga::COhumein_Conga(CGameObject* m, float x, float y) :CGameObject(x, y)
{
	player = m;
	this->ax = 0;
	this->ay = OHUMEIN_CONGA_GRAVITY;
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
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<COhumein_Conga*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void COhumein_Conga::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);

	if ((state == OHUMEIN_CONGA_STATE_WALKING) && (x > maxX || x < minX)) {
		vx = -vx;
	}
	if ((state == OHUMEIN_CONGA_STATE_DIE) && (GetTickCount64() - die_start > OHUMEIN_CONGA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void COhumein_Conga::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_OHUMEIN_CONGA_WALKING;
	switch (state)
	{
	case OHUMEIN_CONGA_STATE_DIE:
		aniId = ID_ANI_OHUMEIN_CONGA_DIE;
		break;
	case OHUMEIN_CONGA_STATE_ATTACK_NEAR:
		aniId = ID_ANI_OHUMEIN_CONGA_ATTACK_NEAR;
		break;
	case OHUMEIN_CONGA_STATE_ATTACK_FAR:
		aniId = ID_ANI_OHUMEIN_CONGA_ATTACK_FAR;
		break;
	case OHUMEIN_CONGA_STATE_TURNING:
		aniId = ID_ANI_OHUMEIN_CONGA_TURNING;
		break;
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
		isDisplay = false;
		isEnable = false;
		break;
	case OHUMEIN_CONGA_STATE_WALKING:
		vx = -OHUMEIN_CONGA_WALKING_SPEED;
		break;
	case OHUMEIN_CONGA_STATE_ATTACK_FAR:
	case OHUMEIN_CONGA_STATE_ATTACK_NEAR:
	case OHUMEIN_CONGA_STATE_TURNING:
		break;
	}
}
