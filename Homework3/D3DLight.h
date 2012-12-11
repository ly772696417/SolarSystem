#pragma once

#include "header.h"

class CD3DLight
{
public:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	CD3DLight(LPDIRECT3DDEVICE9 pD3DDevice);
	~CD3DLight(void);

	void SetLight(D3DXVECTOR3 pos);
};

