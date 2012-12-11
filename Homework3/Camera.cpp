#include "Camera.h"

CCamera::CCamera()
{
	m_cameraType = CameraType::AIRCRAFT;

	g_vPos		= D3DXVECTOR3(0.0f, 30.0f, 0.0f);
	g_vRight	= D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	g_vUp		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	g_vLook		= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
}

CCamera::~CCamera()
{
}

void CCamera::strafe(float units){

	if (m_cameraType == CameraType::AIRCRAFT)
	{
		g_vPos += g_vRight * units;
	}
	else
	{
		g_vPos += D3DXVECTOR3(g_vRight.x,0.0f,g_vRight.z);
	}
}

void CCamera::fly(float units){
	if (m_cameraType == CameraType::AIRCRAFT)
	{
		g_vPos += g_vUp * units;
	}
	else
	{
		g_vPos.y += units;
	}
	
}

void CCamera::walk(float units){
	if (m_cameraType == CameraType::AIRCRAFT)
	{
		g_vPos += g_vLook * units;
	}
	else
	{
		g_vPos += D3DXVECTOR3(g_vLook.x,0.0f,g_vLook.z);
	}
}

void CCamera::pitch(float angle){
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T,&g_vRight,angle);

	D3DXVec3TransformCoord(&g_vLook,&g_vLook,&T);
	D3DXVec3TransformCoord(&g_vUp,&g_vUp,&T);
}

void CCamera::yaw(float angle){
	D3DXMATRIX T;

	if (m_cameraType == CameraType::LANDOBJECT)
	{
		D3DXMatrixRotationY(&T,angle);
	}
	if (m_cameraType == CameraType::AIRCRAFT)
	{
		D3DXMatrixRotationAxis(&T,&g_vUp,angle);
	}

	D3DXVec3TransformCoord(&g_vLook,&g_vLook,&T);
	D3DXVec3TransformCoord(&g_vRight,&g_vRight,&T);
}

void CCamera::roll(float angle){
	if (m_cameraType == CameraType::AIRCRAFT)
	{
		D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T,&g_vLook,angle);

		D3DXVec3TransformCoord(&g_vUp,&g_vUp,&T);
		D3DXVec3TransformCoord(&g_vRight,&g_vRight,&T);
	}
}

void CCamera::getViewMatrix(D3DXMATRIX *V)
{
	D3DXVec3Normalize(&g_vLook, &g_vLook);

	D3DXVec3Cross(&g_vUp, &g_vLook, &g_vRight);
	D3DXVec3Normalize(&g_vUp, &g_vUp);

	D3DXVec3Cross(&g_vRight, &g_vUp, &g_vLook);
	D3DXVec3Normalize(&g_vRight, &g_vRight);

	float x = -D3DXVec3Dot(&g_vRight, &g_vPos);
	float y = -D3DXVec3Dot(&g_vUp   , &g_vPos);
	float z = -D3DXVec3Dot(&g_vLook , &g_vPos);

	V->_11 = g_vRight.x; V->_12 = g_vUp.x; V->_13 = g_vLook.x; V->_14 = 0.0f;
	V->_21 = g_vRight.y; V->_22 = g_vUp.y; V->_23 = g_vLook.y; V->_24 = 0.0f;
	V->_31 = g_vRight.z; V->_32 = g_vUp.z; V->_33 = g_vLook.z; V->_34 = 0.0f;
	V->_41 = x         ; V->_42 = y      ; V->_43 = z        ; V->_44 = 1.0f;
}

void CCamera::getPosition(D3DXVECTOR3 *pos)
{
	*pos = g_vPos;
}

void CCamera::setPosition(const D3DXVECTOR3 *pos)
{
	g_vPos = *pos;
}

void CCamera::ProcInput(GameInput *gameInput)
{ 
	float fDelta = 0.005f;
	
	float x = gameInput->m_CurMState.pos.x - gameInput->m_OldMState.pos.x;
	float y = gameInput->m_CurMState.pos.y - gameInput->m_OldMState.pos.y;

	pitch(y * fDelta * 0.5);
	yaw(x * fDelta * 0.5);

	if(KEYDOWN('W'))
	{
		walk(5000.0f * fDelta);
	}
	if(KEYDOWN('S'))
	{
		walk(-5000.0f * fDelta);
	}
	if(KEYDOWN('A'))
	{
		strafe(-5000.0f * fDelta);
	}
	if(KEYDOWN('D'))
	{
		strafe(5000.0f * fDelta);
	}

	return;
}