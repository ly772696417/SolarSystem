//程序中创建sphere
#pragma once
#include "header.h"
#include "Vertex.h"

class CSphereMesh
{
private:

	LPDIRECT3DDEVICE9 m_pD3DDevice; 

	BoundingSphere m_BoundingSphere;    //包围球的结构
	LPD3DXMESH m_pSphere;					 //指向球的mesh指针

	LPDIRECT3DTEXTURE9 m_pTexture;


public:
	CSphereMesh(LPDIRECT3DDEVICE9  pD3DDevice);
	~CSphereMesh(void);

	HRESULT InitMesh();
	LPD3DXMESH CreateMappedSphere(LPDIRECT3DDEVICE9 pDev,float fRad,UINT slices,UINT stacks);
	BOOL  SetTexture(const char *TextureFilePath);
	void SetMaterial();
	void Render();
};
