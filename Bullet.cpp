#include "Bullet.h"
#include "Chowmein_Conga.h"
#include "Locust.h"
#include "Debug.h"
#include "Collision.h"
#include "Marco.h"
#include "PlayScene.h"
#include "Game.h"
Bullet::Bullet(float x, float y, float dir, int animation,int ncounter) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	if (animation != 2)
		this->vx = BULLET_SPEED * dir;
	else
		this->vx = BULLET_SPEED / 5 * dir;
	this->anim = animation;
	this->bcounter = ncounter;
	this->start_time = GetTickCount64();
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
	CMARCO* MARCO = (CMARCO*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	if (anim == 2 && GetTickCount64() - start_time > 400)
	{
		vx = BULLET_SPEED/1.5;
	}
	vy += ay * dt;
	vx += ax * dt;
	float mx, my;
	MARCO->GetPosition(mx, my);
	if (this->x > mx + 300)
		isDeleted = true;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void Bullet::Render()
{
	CAnimations* animations = CAnimations::GetInstance();

	int aniId = ID_ANI_PISTOL_BULLET;
	if (anim == 1)
		aniId = ID_ANI_MG_BULLET;
	else if (anim == 2)
	{
		aniId = ID_ANI_ROCKET_BULLET + bcounter * 10;
		animations->Get(aniId)->Render(x, y, 1);
		RenderBoundingBox();
		return;
	}
	animations->Get(aniId)->Render(x, y, 1);
	RenderBoundingBox();

}
