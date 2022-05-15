#include "Camera.h"
#include "Game.h"
#include <cstddef>
#include "Marco.h"

CCamera* CCamera::__instance = NULL;

CCamera::CCamera()
{
	cam_x = 0;
	cam_y = 0;

	boundary_right = 0;
	boundary_top = 0;
}

CCamera::CCamera(float x, float y)
{
	cam_x = x;
	cam_y = y;

	boundary_right = 0;
	boundary_top = 0;
}

void CCamera::SetCamPosition(float x, float y)
{
	//x, y is player's position
	float campos_x = x - SCREEN_WIDTH / 2;
	float campos_y = y - SCREEN_HEIGHT / 2 - MARCO_BIG_BBOX_HEIGHT;
	bool flag_x = true; //if true update cam_x
	bool flag_y = true; //if true update cam_y
	if (campos_x < 0 || campos_x > boundary_right)
		flag_x = false;
	if (campos_y < 0 || campos_y > boundary_top)
		flag_y = false;
	if (flag_x)
	{
		cam_x = campos_x;
	}
	if (flag_y)
	{
		cam_y = campos_y;
	}
}

void CCamera::SetBoundary(float w, float h)
{
	boundary_right = w;
	boundary_top = h;
}

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL)
		__instance = new CCamera();
	return __instance;
}