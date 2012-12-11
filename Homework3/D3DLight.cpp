#include "D3DLight.h"


CD3DLight::CD3DLight(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
}


CD3DLight::~CD3DLight(void)
{
}

void CD3DLight::SetLight(D3DXVECTOR3 pos){
	D3DLIGHT9 light;
	ZeroMemory(&light,sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_POINT;
	light.Diffuse.r = 1.0f;
	light.Diffuse.g = 1.0f;
	light.Diffuse.b  =1.0f;
	light.Attenuation1 = 0.00006f;
	light.Range = 30000.0f;
	light.Position = pos;

	m_pD3DDevice->SetLight(0,&light);
	m_pD3DDevice->LightEnable(0,TRUE);

	m_pD3DDevice->SetRenderState(D3DRS_AMBIENT,D3DCOLOR_XRGB(16,16,16));
	m_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS,true);
	m_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE,true);
}
