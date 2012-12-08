#pragma once

#include "header.h"
#include "D3DDrawScence.h"

class D3DInit
{
public:
	D3DInit(void);
	~D3DInit(void);

	BOOL GameInit(HWND hWnd,HINSTANCE hInstance);
	HRESULT InitD3D(HWND hWnd);
	void Render();

private:
	LPDIRECT3D9  g_pD3D;
	LPDIRECT3DDEVICE9  g_pD3DDevice;

	D3DDrawScence *g_pDrawScence;
};

