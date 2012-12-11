#include "GameInput.h"


GameInput::GameInput(void)
{
	m_pDI = NULL;
	m_pMouse = NULL;

	m_OldMState.left = false;
	m_OldMState.right = false;
	m_OldMState.pos.x = GetSystemMetrics(SM_CXSCREEN) * 0.5;
	m_OldMState.pos.y = GetSystemMetrics(SM_CYSCREEN) * 0.5;

	m_CurMState.left = false;
	m_CurMState.right = false;
	m_CurMState.pos.x = GetSystemMetrics(SM_CXSCREEN) * 0.5;
	m_CurMState.pos.y = GetSystemMetrics(SM_CYSCREEN) * 0.5;
}


GameInput::~GameInput(void)
{
	if (m_pMouse)
	{
		m_pMouse->Release();
		m_pMouse = NULL;
	}

	if(m_pDI){
		m_pDI->Release();
		m_pDI = NULL;
	}
}

BOOL GameInput::InitInput(HWND hWnd,HINSTANCE hInstance){
	HRESULT result;
	result = DirectInput8Create(hInstance,
							DIRECTINPUT_VERSION,
							IID_IDirectInput8,
							(LPVOID *)&m_pDI,
							NULL
							);

	if (DI_OK != result)
	{
		MessageBox(NULL,"建立DirectInput对象失败",NULL,MB_OK);
		return false;
	}

	m_pDI->CreateDevice(GUID_SysMouse,&m_pMouse,NULL);
	m_pMouse->SetDataFormat(&c_dfDIMouse2);
	m_pMouse->SetCooperativeLevel( hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE );

	DIPROPDWORD property;
	property.diph.dwSize = sizeof(DIPROPDWORD);
	property.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	property.diph.dwHow = DIPH_DEVICE;
	property.diph.dwObj = 0;
	property.dwData = DINPUT_BUFFERSIZE;

	m_pMouse->SetProperty(DIPROP_BUFFERSIZE,&property.diph);
	m_pMouse->Acquire();

	return true;
}


BOOL GameInput::ReadMouse(){

	HRESULT result;
	DIMOUSESTATE2 dims2;
	ShowCursor(FALSE);

	if (NULL == m_pMouse)
	{
		MessageBox(NULL,"鼠标设备出错！",NULL,MB_OK);
		return false;
	}
	ZeroMemory(&dims2,sizeof(dims2));
	result = m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE2),&dims2);

	if (result != DI_OK)
	{
		MessageBox(NULL,"鼠标获得设备状态失败！",NULL,MB_OK);
		return false;
	}
	result = m_pMouse->Acquire();

	while (result == DIERR_INPUTLOST)
	{
		result = m_pMouse->Acquire();
	}

	m_OldMState.left = m_CurMState.left;
	m_OldMState.right = m_CurMState.right;
	m_OldMState.pos.x = m_CurMState.pos.x;
	m_OldMState.pos.y = m_CurMState.pos.y;

	m_CurMState.pos.x += dims2.lX;
	m_CurMState.pos.y += dims2.lY;

	if(dims2.rgbButtons[0] & 0x80){
		m_CurMState.left = true;
	}
	else
	{
		m_CurMState.left= false;
	}

	if (dims2.rgbButtons[1] & 0x80)
	{
		m_CurMState.right = true;
	}
	else
	{
		m_CurMState.right = false;
	}

	return true;
}