#pragma once
#include "header.h"

typedef struct _VERTEX
{
    D3DXVECTOR3 pos;     // vertex position
    D3DXVECTOR3 norm;    // vertex normal
    float tu;            // texture coordinates
    float tv;
} VERTEX,*LPVERTEX;

#define FVF_VERTEX    D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1

class CSphereMap
{
private:
	LPDIRECT3DDEVICE9            m_pd3dDevice;
	LPD3DXMESH                   m_pSphere;
	LPDIRECT3DTEXTURE9           m_pTexture;

public:
	LPD3DXMESH CreateMappedSphere(LPDIRECT3DDEVICE9 pDev,float fRad,
		                                    UINT slices,UINT stacks);
	CSphereMap(LPDIRECT3DDEVICE9 pD3DDevice);
	~CSphereMap(void);
	BOOL  SetTexture(const char *TextureFilePath);
	void  SetMatrices();
	void  Render();
};
