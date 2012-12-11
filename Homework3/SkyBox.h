#pragma once

#include "header.h"
#include "Vertex.h"

class CSkyBox
{
private:
	LPDIRECT3DDEVICE9            m_pD3DDevice;
	LPDIRECT3DVERTEXBUFFER9      m_pVB;
	LPDIRECT3DINDEXBUFFER9       m_pIB;
	LPDIRECT3DTEXTURE9           m_pTextrue[6];

public:
	CSkyBox(LPDIRECT3DDEVICE9  g_pD3DDevice);
	~CSkyBox(void);
	HRESULT  InitSkyBox(int scale);
	void     Render(D3DXVECTOR3 CamPos);
	bool     SetTexture( const char *TextureFile, int flag);
};

