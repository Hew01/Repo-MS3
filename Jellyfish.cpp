#include "Jellyfish.h"
#include "Marco.h"
#include "Game.h"

CJellyfish::CJellyfish(CGameObject* m, float x, float y) :CGameObject(x, y)
{
	player = m;
	this->ax = 0;
	this->ay = JELLYFISH_GRAVITY;
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
	SetState(JELLYFISH_STATE_WALKING);
}

void CJellyfish::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - JELLYFISH_BBOX_WIDTH / 2;
	top = y - JELLYFISH_BBOX_HEIGHT / 2;
	right = left + JELLYFISH_BBOX_WIDTH;
	bottom = top + JELLYFISH_BBOX_HEIGHT;
}

void CJellyfish::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CJellyfish::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CJellyfish*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CJellyfish::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);

	if ((state == JELLYFISH_STATE_WALKING) && (x > maxX || x < minX)) {
		vx = -vx;
	}
	if ((state == JELLYFISH_STATE_DIE) && (GetTickCount64() - die_start > JELLYFISH_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CJellyfish::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_JELLYFISH_WALKING;
	switch (state)
	{
	case JELLYFISH_STATE_DIE:
		aniId = ID_ANI_JELLYFISH_DIE;
		break;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();
}

void CJellyfish::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case JELLYFISH_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		ay = 0;
		isDisplay = false;
		isEnable = false;
		break;
	case JELLYFISH_STATE_WALKING:
		vx = -JELLYFISH_WALKING_SPEED;
		break;
	}
}
