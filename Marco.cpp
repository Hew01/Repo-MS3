#include <algorithm>
#include "debug.h"

#include "Marco.h"
#include "Chowmein_Conga.h"
#include "Game.h"
#include "Portal.h"
#include "Bullet.h"
#include "PlayScene.h"

#include "Collision.h"
#include <iostream>
#define CURRENT_SCENE ((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())

void CMARCO::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	
	// reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARCO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	isOnPlatform = false;
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMARCO::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMARCO::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (e->ny != 0 && e->obj->IsBlocking())
	{
		vy = 0;
		if (e->ny < 0) isOnPlatform = true;
	}
	else
		if (e->nx != 0 && e->obj->IsBlocking())
		{
			vx = 0;
		}

	if (dynamic_cast<Chowmein_Conga*>(e->obj))
		OnCollisionWithChowmeinConga(e);
	//else if (dynamic_cast<CCoin*>(e->obj))
	//	OnCollisionWithCoin(e);
	else if (dynamic_cast<Portal*>(e->obj))
		OnCollisionWithPortal(e);
}

void CMARCO::OnCollisionWithChowmeinConga(LPCOLLISIONEVENT e)
{
	Chowmein_Conga* chowmein = dynamic_cast<Chowmein_Conga*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (chowmein->GetState() != CHOWMEIN_CONGA_STATE_DIE)
		{
			chowmein->SetState(CHOWMEIN_CONGA_STATE_DIE);
			vy = -MARCO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		/*if (killing)
		{
				chowmein->SetState(CHOWMEIN_CONGA_STATE_DIE);
		}*/
	}
}
//
//void CMARCO::OnCollisionWithCoin(LPCOLLISIONEVENT e)
//{
//	e->obj->Delete();
//	coin++;
//}
//
void CMARCO::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	Portal* p = (Portal*)e->obj;
	CGame::GetInstance()->InitiateSwitchScene(p->GetSceneId());
}


//
// Get animdation ID for big MARCO
//
int CMARCO::GetAniId()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (nx >= 0)
			aniId = ID_ANI_MARCO_JUMP_WALK_RIGHT;
		else
			aniId = ID_ANI_MARCO_JUMP_WALK_LEFT;
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARCO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARCO_SIT_LEFT;
		}
		else
			if (vx == 0)
			{
				if (nx > 0) aniId = ID_ANI_MARCO_IDLE_RIGHT;
				else aniId = ID_ANI_MARCO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				aniId = ID_ANI_MARCO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				aniId = ID_ANI_MARCO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARCO_IDLE_RIGHT;
	if (shooting) aniId = ID_ANI_MARCO_SHOOTING_RIGHT;
	return aniId;
}
int CMARCO::GetAniIdLeg()
{
	int aniId = -1;
	if (vx == 0)
	{
		if (nx > 0) aniId = ID_ANI_LEG_IDLE;
		else aniId = ID_ANI_LEG_IDLE;
	}
	else if (vx > 0)
	{
		aniId = ID_ANI_LEG_RUN;
	}
	else // vx < 0
	{
		aniId = ID_ANI_LEG_RUN;
	}

	if (aniId == -1) aniId = ID_ANI_LEG_IDLE;

	return aniId;
}
void CMARCO::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	CAnimations* animationsLeg = CAnimations::GetInstance();
	int aniId = -1;
	int aniIdLeg = ID_ANI_LEG_IDLE;

	if (state == MARCO_STATE_DIE)
		aniId = ID_ANI_MARCO_DIE;
	else
	{
		aniId = GetAniId();
		aniIdLeg = GetAniIdLeg();
	}
	if (shooting) {
		animationsLeg->Get(aniIdLeg)->Render(x, y + 15);
		animations->Get(aniId)->Render(x + 8, y);
	}
	else {
		animationsLeg->Get(aniIdLeg)->Render(x, y + 15);
		animations->Get(aniId)->Render(x + 5, y);
	}

	//RenderBoundingBox();

	//DebugOutTitle(L"Coins: %d", coin);
}

void CMARCO::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARCO_STATE_DIE) return;

	switch (state)
	{
	case MARCO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		vx = MARCO_WALKING_SPEED;
		nx = 1;
		break;
	case MARCO_STATE_WALKING_LEFT:
		if (isSitting) break;
		vx = -MARCO_WALKING_SPEED;
		nx = -1;
		break;
	case MARCO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			vy = -MARCO_JUMP_SPEED_Y;
		}
		break;

	case MARCO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARCO_JUMP_SPEED_Y / 2;
		break;

	case MARCO_STATE_SIT:
		if (isOnPlatform)
		{
			state = MARCO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARCO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARCO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARCO_STATE_IDLE;
			y -= MARCO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARCO_STATE_IDLE:
		ax = 0.0f;
		vx = 0.0f;
		break;

	case MARCO_STATE_SHOOTING:
		shooting = true;
		break;
	case MARCO_STATE_SHOOT_RELEASE:
		shooting = false;
		first_shot = true;
		break;
	case MARCO_STATE_DIE:
		vy = -MARCO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		break;
	}

	CGameObject::SetState(state);
}


void CMARCO::Shoot() {
	int delay;
	if (first_shot) delay = 150;
	else delay = 600;
	if (last_shot == -1){
		last_shot = GetTickCount64();
	}
	else if (GetTickCount64() - last_shot > delay) {
		first_shot = false;
		last_shot = GetTickCount64();
		if (bullet > 0)
		{
			bullet -= 1;
			CGameObject* obj = NULL;
			obj = new Bullet(x + 16, y, nx);
			CURRENT_SCENE->AddObject(obj);
		}
	}
}
void CMARCO::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (isSitting)
	{
		left = x - MARCO_BIG_SITTING_BBOX_WIDTH / 2;
		top = y - MARCO_BIG_SITTING_BBOX_HEIGHT / 2;
		right = left + MARCO_BIG_SITTING_BBOX_WIDTH;
		bottom = top + MARCO_BIG_SITTING_BBOX_HEIGHT;
	}
	else
	{
		left = x - MARCO_BIG_BBOX_WIDTH / 2;
		top = y - MARCO_BIG_BBOX_HEIGHT / 2;
		right = left + MARCO_BIG_BBOX_WIDTH;
		bottom = top + MARCO_BIG_BBOX_HEIGHT;
	}
}


