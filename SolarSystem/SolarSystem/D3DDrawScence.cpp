#include "D3DDrawScence.h"


D3DDrawScence::D3DDrawScence(LPDIRECT3DDEVICE9 D3DDevice)
{
	m_pD3DDevice = D3DDevice;
}


D3DDrawScence::~D3DDrawScence(void)
{
}

void D3DDrawScence::Init(HWND hWnd,HINSTANCE hInstance){
	Debug *debug1 = new Debug();
	//debug1->LogMsg("%s %d","this is init",debug1->getmNum());

	m_pGameInput.InitInput(hWnd,hInstance);
}

void D3DDrawScence::Render(){
	SetInput();
	Debug *debug2 = new Debug();
	//debug2->LogMsg("%s %d","this is render",debug2->getmNum());
}

void D3DDrawScence::SetInput(){
	m_pGameInput.ReadMouse();
	Debug *debug3 = new Debug();
	debug3->LogMsg("%d",m_pGameInput.m_CurMState.pos.x);
	debug3->LogMsg("%d",m_pGameInput.m_CurMState.pos.y);
}