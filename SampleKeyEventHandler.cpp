#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Marco.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMARCO* MARCO = (CMARCO*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		MARCO->SetState(MARCO_STATE_SIT);
		break;
	case DIK_S:
		MARCO->SetState(MARCO_STATE_JUMP);
		break;
	case DIK_0:
		MARCO->SetState(MARCO_STATE_DIE);
		break;
	case DIK_A:
		MARCO->SetState(MARCO_STATE_SHOOTING);
		break;

	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMARCO* MARCO = (CMARCO*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		MARCO->SetState(MARCO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		MARCO->SetState(MARCO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		MARCO->SetState(MARCO_STATE_SHOOT_RELEASE);
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMARCO* MARCO = (CMARCO*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		MARCO->SetState(MARCO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		MARCO->SetState(MARCO_STATE_WALKING_LEFT);
	}
	else
		MARCO->SetState(MARCO_STATE_IDLE);
	if (game->IsKeyDown(DIK_A))
		MARCO->Shoot();
	if (game->IsKeyDown(DIK_1))
		MARCO->SetWeapon(0);
	if (game->IsKeyDown(DIK_2))
		MARCO->SetWeapon(1);
	if (game->IsKeyDown(DIK_3))
		MARCO->SetWeapon(2);

}