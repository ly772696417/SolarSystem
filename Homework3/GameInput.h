#pragma once

#include "header.h"

class GameInput
{
public:
	LPDIRECTINPUT8 m_pDI;
	LPDIRECTINPUTDEVICE8 m_pMouse;

	MSTATE m_OldMState;
	MSTATE m_CurMState;

	int MouseX;
	int MouseY;

public:
	GameInput(void);
	~GameInput(void);

	BOOL InitInput(HWND hWnd,HINSTANCE hInstance);
	BOOL ReadMouse();
};

