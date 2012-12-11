#pragma once

#include "header.h"
#include "GameInput.h"

enum CameraType
{
	LANDOBJECT,
	AIRCRAFT
};

class CCamera
{
public:
	CCamera();
	virtual ~CCamera();

	void strafe(float units);//right
	void fly(float uints);//up
	void walk(float units);//look

	void pitch(float angle);//right ¸©Ñö
	void yaw(float angle);//up Æ«º½
	void roll(float angle);//look ¹ö¶¯

	void getViewMatrix(D3DXMATRIX *V);
	void getPosition(D3DXVECTOR3 *pos);
	void setPosition(const D3DXVECTOR3 *pos);

	void ProcInput(GameInput *gameInput);

public:
	D3DXVECTOR3		g_vRight;
	D3DXVECTOR3		g_vUp;
	D3DXVECTOR3		g_vLook;
	D3DXVECTOR3		g_vPos;

	CameraType m_cameraType;
};

