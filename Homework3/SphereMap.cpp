#include ".\spheremap.h"
#include "header.h"

CSphereMap::CSphereMap(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pd3dDevice = pD3DDevice;
	m_pSphere    = CreateMappedSphere(m_pd3dDevice,10.0f,100,100);
}

CSphereMap::~CSphereMap(void)
{
}
LPD3DXMESH CSphereMap::CreateMappedSphere(LPDIRECT3DDEVICE9 pDev,float fRad,
		                                    UINT slices,UINT stacks)
{
	// create the sphere
    LPD3DXMESH mesh;
    if (FAILED(D3DXCreateSphere(pDev,fRad,slices,stacks,&mesh,NULL)))
        return NULL;
    // create a copy of the mesh with texture coordinates,
    // since the D3DX function doesn't include them
    LPD3DXMESH texMesh;
    if (FAILED(mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM,FVF_VERTEX,pDev,&texMesh)))
        // failed, return un-textured mesh
        return mesh;

    // finished with the original mesh, release it
    mesh->Release();

    // lock the vertex buffer
    LPVERTEX pVerts;
 if (SUCCEEDED(texMesh->LockVertexBuffer(0,(LPVOID*) &pVerts))) {

        // get vertex count
        int numVerts = texMesh->GetNumVertices();

        // loop through the vertices
        for (int i=0;i<numVerts;i++) {

            // calculate texture coordinates
            pVerts->tu=asinf(pVerts->norm.x)/D3DX_PI+0.5f;
            pVerts->tv=asinf(pVerts->norm.y)/D3DX_PI+0.5f;
            
            // go to next vertex
            pVerts++;
        }

        // unlock the vertex buffer
        texMesh->UnlockVertexBuffer();
    }
    
    // return pointer to caller
	
    return texMesh;

}


void  CSphereMap::SetMatrices()
{

	D3DXMATRIX matView, matProj,matWorld;

	D3DXMatrixRotationY(&matWorld,timeGetTime()/4000.f);

    m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXMatrixLookAtLH(&matView,&D3DXVECTOR3(0.0f, 0.0f, -30.0f),
		                        &D3DXVECTOR3(0.0f, 0.0f, 0.0f), 
								&D3DXVECTOR3(0.0f, 1.0f,  0.0f));
	m_pd3dDevice->SetTransform(D3DTS_VIEW,&matView);

	D3DXMatrixPerspectiveFovLH(&matProj,D3DX_PI/2, 1024.0f/768.0f, 1.0f, 100.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION,&matProj);

}
BOOL  CSphereMap::SetTexture(const char *TextureFilePath)
{
	if(FAILED(D3DXCreateTextureFromFile(m_pd3dDevice,TextureFilePath
		                               ,&m_pTexture)))
	{
		return false;

	}

	return true;
}


void CSphereMap::Render()
{
	SetMatrices();
    m_pd3dDevice->SetTexture(0,m_pTexture);
	m_pSphere->DrawSubset(0); 

}

