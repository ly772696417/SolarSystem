#include "D3DInit.h"


D3DInit::D3DInit(void)
{
	g_pD3D = NULL;
	g_pD3DDevice = NULL;
}


D3DInit::~D3DInit(void){
	g_pD3D->Release();
	g_pD3D = NULL;

	g_pD3DDevice->Release();
	g_pD3DDevice = NULL;

}

BOOL D3DInit::GameInit(HWND hWnd,HINSTANCE hInstance){
	if (SUCCEEDED(this->InitD3D(hWnd)))
	{
		g_pDrawScence = new D3DDrawScence(g_pD3DDevice);
		g_pDrawScence->Init(hWnd,hInstance);
		return TRUE;
	}
	else
	{
		return FALSE;
	}

	return TRUE;
}

HRESULT D3DInit::InitD3D(HWND hWnd){
	if (!(g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DDISPLAYMODE d3ddm;
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.BackBufferFormat = d3ddm.Format;
	d3dpp.BackBufferHeight = d3ddm.Height;
	d3dpp.BackBufferWidth = d3ddm.Width;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;

	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
														D3DDEVTYPE_HAL,
														hWnd,
														D3DCREATE_SOFTWARE_VERTEXPROCESSING,
														&d3dpp,
														&g_pD3DDevice
														)
		))
	{
		return E_FAIL;
	}

	return S_OK;
}

void D3DInit::Render(){
	if (NULL == g_pD3DDevice)
	{
		return;
	}

	g_pD3DDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0,0,0),1.0f,0);
	g_pD3DDevice->BeginScene();
	
	g_pDrawScence->Render();

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL,NULL,NULL,NULL);
}
