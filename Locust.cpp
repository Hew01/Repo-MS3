#include "Locust.h"
#include "Marco.h"
#include "Game.h"
CLocust::CLocust(CGameObject* m, float x, float y) :CGameObject(x, y)
{
	player = m;
	this->ax = 0;
	this->ay = 0;
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
	SetState(LOCUST_STATE_FLYING);
}

void CLocust::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - LOCUST_BBOX_WIDTH / 2;
	top = y - LOCUST_BBOX_HEIGHT / 2;
	right = left + LOCUST_BBOX_WIDTH;
	bottom = top + LOCUST_BBOX_HEIGHT;
}

void CLocust::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == LOCUST_STATE_FLYING)
	vy += ay * dt;
	vx += ax * dt;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);

	DebugOut(L"Player: X= %d, Y= %d\n", posX, posY);
	DebugOut(L"Locust: X= %d, Y= %d\n", x, y);

	if ((state == LOCUST_STATE_FLYING) && (x > maxX || x < minX)) {
		vx = -vx;
	}

	if ((state == LOCUST_STATE_DIE) && (GetTickCount64() - die_start > LOCUST_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CLocust::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CLocust::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CLocust*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CLocust::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ID_ANI_LOCUST_FLYING;
	if (state == LOCUST_STATE_DIE) {
		aniId = ID_ANI_LOCUST_CATCH_DIE;
	} else if (state == LOCUST_STATE_ATTACKING) {
		aniId = ID_ANI_LOCUST_ATTACKING;
	} else if (state == LOCUST_STATE_TURNING) {
		aniId = ID_ANI_LOCUST_TURNING;
	} else if (state == LOCUST_STATE_PRE_ATTACK) {
		aniId = ID_ANI_LOCUST_PRE_ATTACK;
	} else if (state == LOCUST_STATE_CATCH_PLAYER) {
		aniId = ID_ANI_LOCUST_CATCH_PLAYER;
	} else if (state == LOCUST_STATE_EATING) {
		aniId = ID_ANI_LOCUST_EATING;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	// RenderBoundingBox();
}

void CLocust::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LOCUST_STATE_DIE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		isDisplay = false;
		isEnable = false;
		break;
	case LOCUST_STATE_FLYING:
		vx = -LOCUST_WALKING_SPEED;
	case LOCUST_STATE_ATTACKING:
	case LOCUST_STATE_TURNING:
	case LOCUST_STATE_PRE_ATTACK:
	case LOCUST_STATE_CATCH_PLAYER:
	case ID_ANI_LOCUST_CATCH_PLAYER:
		break;
	}
}
