#include "Enormous.h"
#include "Marco.h"
#include "Game.h"
CEnormous::CEnormous(CGameObject* m, float x, float y) :CGameObject(x, y)
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
		this->minX = ENORMOUS_BBOX_WIDTH;
		this->maxX = SCREEN_WIDTH - ENORMOUS_BBOX_WIDTH;
	}
	else {
		this->minX = posX - SCREEN_WIDTH / 2 + ENORMOUS_BBOX_WIDTH;
		this->maxX = posX + SCREEN_WIDTH / 2 - ENORMOUS_BBOX_WIDTH;
	}
	die_start = -1;
	start_turning = -1;
	start_eating = -1;
	SetState(ENORMOUS_STATE_IDLE);
}

void CEnormous::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - ENORMOUS_BBOX_WIDTH / 2;
	top = y - ENORMOUS_BBOX_HEIGHT / 2;
	right = left + ENORMOUS_BBOX_WIDTH;
	bottom = top + ENORMOUS_BBOX_HEIGHT;
}

void CEnormous::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == ENORMOUS_STATE_IDLE)
		vy += ay * dt;
	vx += ax * dt;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);

	DebugOut(L"Player: X= %d, Y= %d\n", posX, posY);
	DebugOut(L"Locust: X= %d, Y= %d\n", x, y);

	if ((state == ENORMOUS_STATE_ATTACK) && (x > maxX || x < minX)) {
		vx = 0;
	}

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEnormous::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CEnormous::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CEnormous*>(e->obj)) return;

	/*if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}*/
}

void CEnormous::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = ENORMOUS_STATE_IDLE;
	if (state == ENORMOUS_STATE_IDLE) {
		aniId = ID_ANI_ENORMOUS_IDLE_ATTACK;
	}
	else if (state == ENORMOUS_STATE_ATTACK) {
		aniId = ID_ANI_ENORMOUS_IDLE_ATTACK;
	}
	else if (state == ENORMOUS_STATE_CRASHING_AGAIN) {
		aniId = ID_ANI_ENORMOUS_CRASHING_AGAIN;
	}
	else if (state == ENORMOUS_STATE_RETURN) {
		aniId = ID_ANI_ENORMOUS_RETURN;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();
}

void CEnormous::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ENORMOUS_STATE_IDLE:
		die_start = GetTickCount64();
		vx = 0;
		vy = 0;
		isDisplay = false;
		isEnable = false;
		break;
	case ENORMOUS_STATE_ATTACK:
		vx = ENORMOUS_WALKING_SPEED;
		break;
	case ENORMOUS_STATE_CRASHING_AGAIN:
		x = SCREEN_WIDTH - ENORMOUS_BBOX_WIDTH / 2;
		y = ENORMOUS_BBOX_HEIGHT;
		vy = ENORMOUS_TURNING_SPEED;
		vx = -ENORMOUS_TURNING_SPEED;
		break;
	case ENORMOUS_STATE_RETURN:
		start_turning = GetTickCount64();
		vy = ENORMOUS_TURNING_SPEED;
		vx = -ENORMOUS_TURNING_SPEED;
		break;
	}
}
