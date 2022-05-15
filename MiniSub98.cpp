#include "MiniSub98.h"
#include "Marco.h"
#include "Game.h"
CMiniSub98::CMiniSub98(CGameObject* m, float x, float y) :CGameObject(x, y)
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
		this->minX = MINISUB_BBOX_WIDTH;
		this->maxX = SCREEN_WIDTH - MINISUB_BBOX_WIDTH;
	}
	else {
		this->minX = posX - SCREEN_WIDTH / 2 + MINISUB_BBOX_WIDTH;
		this->maxX = posX + SCREEN_WIDTH / 2 - MINISUB_BBOX_WIDTH;
	}
	die_start = -1;
	start_turning = -1;
	start_eating = -1;
	SetState(MINISUB_STATE_SWINMING);
}

void CMiniSub98::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - MINISUB_BBOX_WIDTH / 2;
	top = y - MINISUB_BBOX_HEIGHT / 2;
	right = left + MINISUB_BBOX_WIDTH;
	bottom = top + MINISUB_BBOX_HEIGHT;
}

void CMiniSub98::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == MINISUB_STATE_SWINMING)
		vy += ay * dt;
	vx += ax * dt;
	float posX = 0;
	float posY = 0;
	player->GetPosition(posX, posY);

	DebugOut(L"Player: X= %d, Y= %d\n", posX, posY);
	DebugOut(L"Locust: X= %d, Y= %d\n", x, y);


	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMiniSub98::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CMiniSub98::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CMiniSub98*>(e->obj)) return;
}

void CMiniSub98::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = MINISUB_STATE_SWINMING;
	if (state == MINISUB_STATE_SWINMING) {
		aniId = ID_ANI_MINISUB_SWIMING;
	}


	CAnimations::GetInstance()->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();
}

void CMiniSub98::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MINISUB_STATE_SWINMING:
		start_turning = GetTickCount64();
		vy = MINISUB_TURNING_SPEED;
		vx = -MINISUB_TURNING_SPEED;
		break;
	}
}
