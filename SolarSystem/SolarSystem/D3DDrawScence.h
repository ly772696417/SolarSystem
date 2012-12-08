#pragma once

#include "header.h"

#include "GameInput.h"

class D3DDrawScence
{
public:
	D3DDrawScence(LPDIRECT3DDEVICE9 D3DDevice);
	~D3DDrawScence(void);

	void Init(HWND hWnd,HINSTANCE hInstance);
	void Render();

	void SetInput();
	void SetCamera();

private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	GameInput m_pGameInput;

};

