#include "Bullet.h"
#include "Chowmein_Conga.h"
#include "Locust.h"
#include "Collision.h"

Bullet::Bullet(float x, float y) : CGameObject(x, y)
{
	this->ax = BULLET_SPEED;
	this->ay = 0;
}

void Bullet::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - BULLET_BBOX_WIDTH / 2;
	top = y - BULLET_BBOX_HEIGHT / 2;
	right = left + BULLET_BBOX_WIDTH;
	bottom = top + BULLET_BBOX_HEIGHT;
}

void Bullet::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void Bullet::OnCollisionWith(LPCOLLISIONEVENT e)
{
	isDeleted = true; 
	if (dynamic_cast<Chowmein_Conga*>(e->obj))
		OnCollisionWithChowmeinConga(e);
	else if (dynamic_cast<CLocust*>(e->obj))
		OnCollisionWithLocust(e);
}

void Bullet::OnCollisionWithChowmeinConga(LPCOLLISIONEVENT e)
{
	Chowmein_Conga* chowmein = dynamic_cast<Chowmein_Conga*>(e->obj);
	if (chowmein->GetState() != CHOWMEIN_CONGA_STATE_DIE)
	{
		chowmein->SetState(CHOWMEIN_CONGA_STATE_DIE);
	}
}
void Bullet::OnCollisionWithLocust(LPCOLLISIONEVENT e)
{
	CLocust* locust = dynamic_cast<CLocust*>(e->obj);
	if (locust->GetState() != LOCUST_STATE_DIE)
	{
		locust->SetState(LOCUST_STATE_DIE);
	}
}

void Bullet::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void Bullet::Render()
{
	int aniId = ID_ANI_BULLET;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
