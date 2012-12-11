#include "SphereMesh.h"

CSphereMesh::CSphereMesh(LPDIRECT3DDEVICE9  pD3DDevice)
{
	m_pD3DDevice     = pD3DDevice;
	m_pTexture = NULL;
	m_pSphere    = CreateMappedSphere(m_pD3DDevice,1.0f,100,100);
}
CSphereMesh::~CSphereMesh(void)
{
	Release(m_pTexture);
	m_pTexture = NULL;

	Release(m_pSphere);
	m_pSphere = NULL;
}

HRESULT CSphereMesh::InitMesh()
{
	return S_OK;
}

LPD3DXMESH CSphereMesh::CreateMappedSphere(LPDIRECT3DDEVICE9 pDev,
																				float fRad,
																				UINT slices,
																				UINT stacks)
{
    LPD3DXMESH mesh;
    if (FAILED(D3DXCreateSphere(pDev,fRad,slices,stacks,&mesh,NULL)))
        return NULL;
    LPD3DXMESH texMesh;
    if (FAILED(mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM,FVF_VERTEX,pDev,&texMesh)))
        return mesh;
    mesh->Release();

    LPVERTEX pVerts;
	if (SUCCEEDED(texMesh->LockVertexBuffer(0,(LPVOID*) &pVerts))) {
		int numVerts = texMesh->GetNumVertices();
        for (int i=0;i<numVerts;i++) {
            pVerts->tu=asinf(pVerts->norm.x)/D3DX_PI+0.5f;
            pVerts->tv=asinf(pVerts->norm.y)/D3DX_PI+0.5f;
            pVerts++;
        }
        texMesh->UnlockVertexBuffer();
    }
    return texMesh;

}

BOOL  CSphereMesh::SetTexture(const char *TextureFilePath)
{

	if(FAILED(D3DXCreateTextureFromFile(m_pD3DDevice,
															  TextureFilePath,
															  &m_pTexture)))
	{
		return false;
	}

	return true;
}

void CSphereMesh::Render()
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	m_pD3DDevice->SetTexture(0,m_pTexture);
	m_pSphere->DrawSubset(0);

	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CSphereMesh::SetMaterial()
{
	D3DMATERIAL9 mtrl;

	mtrl.Ambient = D3DXCOLOR(0.0,0.0,0.0,1.0);
	mtrl.Diffuse   = D3DXCOLOR(1.0,1.0,1.0,1.0);
	mtrl.Specular = D3DXCOLOR(1.0,1.0,1.0,1.0);
	mtrl.Emissive = D3DXCOLOR(1.0,1.0,1.0,1.0);
	mtrl.Power = 500.0f;

	m_pD3DDevice->SetMaterial(&mtrl);
}


