#pragma once

#include "header.h"

class CMesh
{
private:
	LPDIRECT3DDEVICE9 m_pD3DDevice; 

	LPD3DXMESH m_pMesh;                //指向mesh的对象指针
	LPD3DXPMESH m_pPMesh;            //渐进式网格
	D3DMATERIAL9 *m_pMeshMaterials; 
	LPDIRECT3DTEXTURE9 *m_pMeshTextures; 
	DWORD m_dwNumMaterials; 
	


public:
	CMesh(LPDIRECT3DDEVICE9  pD3DDevice);
	~CMesh(void);

	HRESULT InitMesh( const char *TextureFilePath , int sunFlag);
	bool SetTexture(const char *TextureFile, int flag);
	void Render();
};
