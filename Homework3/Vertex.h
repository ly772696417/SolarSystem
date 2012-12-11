#pragma once
#include "header.h"
struct SkyBoxVertex
{
	SkyBoxVertex(float x, float y, float z, float u, float v);

	D3DXVECTOR3 m_pos;
	D3DXVECTOR2 m_tex0;
};
#define  D3DFVF_SKYBOX (D3DFVF_XYZ | D3DFVF_TEX1 )


struct CUSTOMVERTEX
{
	FLOAT  x,y,z;	
	DWORD  color;
};

#define D3DFVF_CUSTOMVETEX  (D3DFVF_XYZ | D3DFVF_DIFFUSE )


typedef struct _VERTEX
{
    D3DXVECTOR3 pos;     
    D3DXVECTOR3 norm;   
    float tu;    
    float tv;
} VERTEX,*LPVERTEX;

#define FVF_VERTEX    D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1


