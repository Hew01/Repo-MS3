#pragma once
#include "Camera.h"
#define CAMERA_STATE_IDLE	0
#define CAMERA_STATE_MOVE_LEFT	1
#define CAMERA_STATE_MOVE_RIGHT	2

class CCamera
{
	static CCamera* __instance;

	float cam_x; //position of camera at present
	float cam_y; //position of camera at present

	float boundary_right;
	float boundary_top;

	CCamera();
	CCamera(float start_x, float start_y);
public:
	void SetCamPos(float x, float y); //update camera follow player
	void SetBoundary(float w, float h);

	float GetCamPosX() { return cam_x; }
	float GetCamPosY() { return cam_y; }

	static CCamera* GetInstance();

	~CCamera();
};
