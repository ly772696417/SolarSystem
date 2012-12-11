#include "RingLine.h"

#define PI 3.1415926

CRingLine::CRingLine(LPDIRECT3DDEVICE9 pD3DDevice,float radius)
{
	m_Radius = radius;
	m_pd3dDevice = pD3DDevice;

	m_pBufferLine = NULL;
	m_pBufferRec = NULL;
}


CRingLine::~CRingLine(void)
{
	Release(m_pBufferLine);
	m_pBufferLine = NULL;

	Release(m_pBufferRec);
	m_pBufferRec = NULL;
}

HRESULT CRingLine::InitVB(){
	CUSTOMVERTEX g_Vertices[73];

	for (int i = 0; i < 73; i++)
	{
		g_Vertices[i].x = m_Radius*cos(2*PI * i/ 72);
		g_Vertices[i].y = 0.0f;
		g_Vertices[i].z = m_Radius*sin(2*PI * i /72);
		g_Vertices[i].color = D3DCOLOR_XRGB(rand()%256,rand()%256,rand()%256);
	}

	if(FAILED(m_pd3dDevice->CreateVertexBuffer(sizeof(g_Vertices)
		                                       ,0
											   ,D3DFVF_CUSTOMVETEX
											   ,D3DPOOL_MANAGED
											   ,&m_pBufferRec
											   ,NULL)))
	{
		return E_FAIL;
	}

	VOID*  pVertices;
	if(FAILED(m_pBufferRec->Lock(0, 
		sizeof(g_Vertices),(void**)&pVertices,
		                           0)))
	{
		return E_FAIL;
	}
	memcpy(pVertices,g_Vertices,sizeof(g_Vertices));
	m_pBufferRec->Unlock();

	return S_OK;
}

void CRingLine::Render(){

	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1,D3DTA_DIFFUSE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING ,false);

	m_pd3dDevice->SetStreamSource(0, m_pBufferRec,0,sizeof(CUSTOMVERTEX));
    m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVETEX);
    m_pd3dDevice->DrawPrimitive(D3DPT_LINESTRIP,0,72);

	m_pd3dDevice->SetTextureStageState(0, D3DTSS_COLORARG1,D3DTA_TEXTURE);
	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING ,true);
}
