#pragma once

#include "header.h"
#include "DrawScence.h"

class CD3DInit
{
public:
	CD3DInit(void);
	~CD3DInit(void);

	BOOL GameInit(HWND hWnd,HINSTANCE hInstance);
	HRESULT InitD3D(HWND hWnd);
	void Render();

private:
	LPDIRECT3D9  g_pD3D;
	LPDIRECT3DDEVICE9  g_pD3DDevice;

	CDrawScence *g_pDrawScence;
};
