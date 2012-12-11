#pragma once

#include "header.h"
#include "Vertex.h"

class CRingLine
{
public:
	CRingLine(LPDIRECT3DDEVICE9  pD3DDevice,float radius);
	~CRingLine(void);

	HRESULT  InitVB();
	void     Render();

public:
	LPDIRECT3DDEVICE9          m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9    m_pBufferRec;
	LPDIRECT3DVERTEXBUFFER9    m_pBufferLine;

	float m_Radius;
};

