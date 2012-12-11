#include "Mesh.h"

CMesh::CMesh(LPDIRECT3DDEVICE9  pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	m_dwNumMaterials = 0;
	m_pMesh = NULL;
	m_pPMesh = NULL;
	m_pMeshMaterials = NULL;
	m_pMeshTextures = NULL;
}
CMesh::~CMesh(void)
{
	Release(m_pMesh);
	m_pMesh = NULL;

	Release(m_pPMesh);
	m_pPMesh = NULL;
}

HRESULT CMesh::InitMesh(const char *TextureFilePath,int sunFlag)
{
	LPD3DXBUFFER    pAdjBuffer  = 0;
	LPD3DXBUFFER    pD3DXMtrBuffer;
	//���磬���㻺���������ʼ��ϣ������ϵ�Direct3D���ݡ�
	if( FAILED(D3DXLoadMeshFromX( TextureFilePath,
														D3DXMESH_SYSTEMMEM,  //ָ�����ɵĶ������������
														m_pD3DDevice,
														&pAdjBuffer,         //�洢�ڽ��������Ϣ��LPD3DXBUFFER��ַ
														&pD3DXMtrBuffer,     //�洢ģ�Ͳ��ʵ�LPD3DXBUFFER��ַ
														NULL,                //�洢ģ����Ч��LPD3DXBUFFER��ַ
														&m_dwNumMaterials,   //�洢ģ�Ͳ����������ڴ��ַ
														&m_pMesh )))         //�洢���ɵĶ����������ڴ��ַ
	{
		return E_FAIL;
	}

	D3DXMATERIAL  *d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrBuffer->GetBufferPointer();
	//���ݼ��ز��ʵ�����Ϊ���ʺ�������䱣��Ŀռ䡣
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	//ͨ��ѭ����Ϊģ�ʹ�������
	for( DWORD i = 0; i < m_dwNumMaterials; i++ )
	{   //��ģ���еĲ��ʷ��������Լ�����Ĳ��ʿռ���
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		// X��û�л�����Ambient�����������ֱ��������
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		if (sunFlag)
		{
			m_pMeshMaterials[i].Emissive = D3DXCOLOR(1,0.7,0.7,1);
		}
		m_pMeshTextures[i] = NULL;  //����ָ������� 
		//������ʶ�Ӧ�����������ǾͰ�����������
		if (i<5)
		{
			if( d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
			{    
				//��������������ָ����ָ��ָ��
				if(FAILED(D3DXCreateTextureFromFile( m_pD3DDevice, 
					d3dxMaterials[i].pTextureFilename, &m_pMeshTextures[i])))
				{
					int result =  MessageBox(NULL, "TexturesLoadError",
														   "WM_CLOSE Message Processor",
														   MB_OK | MB_ICONQUESTION);
														   exit(0);
				}
			}
		}	
	}
	Release(pD3DXMtrBuffer);

	//�Ż�����
	if(FAILED(m_pMesh->OptimizeInplace( 
		D3DXMESHOPT_ATTRSORT |     //�������Ը����������򲢵������Ա��⽫ʹDrawSubset��������Ч��ִ��
		D3DXMESHOPT_COMPACT  |     //ɾ��û���õĶ����������
		D3DXMESHOPT_VERTEXCACHE,   //���Ӷ��㻺���������
		(DWORD*)pAdjBuffer->GetBufferPointer(), //û���Ż���Mesh���ڽ�����
		(DWORD*)pAdjBuffer->GetBufferPointer(), //����Ż���Mesh���ڽ���Ϣ������
		0, 0)))
	{
		return E_FAIL;
	}

	//���ɽ���ʽ����
	if(FAILED(D3DXGeneratePMesh(m_pMesh,  //�������ͨ��Mesh����
													(DWORD*)pAdjBuffer->GetBufferPointer(),  //Mesh������ڽ���Ϣ
													0, //��ʾ��������Ե�Ȩ���ڼ�Mesh����ʱ��
													//Ȩֵ����һ�����㱻ɾ���Ŀ����Դ�С����
													//����������ΪNULL����ʱ����ʹ��Ĭ�ϵ�Ȩֵ
													0,  // ���ھ��������ڼ�ʱ��ɾ���Ŀ����Ե�
													//��С�ò���Ҳ����ΪNULL��
													//��ʱ������Ĭ�ϵ�ȨֵΪ1.0f��		                                  
													10,// �ڼ�Meshʱ���������������������С����
													D3DXMESHSIMP_FACE, // ֻ��ȡD3DXMESHSIMPö�������е�һ��ֵ��
													// D3DXMESHSIMP_VERTEX �C��һ������MinValueָ������
													// D3DXMESHSIMP_FACE �C��һ������MinValueָ��������
													&m_pPMesh)))
	{
		return E_FAIL;
	} 
	
	DWORD maxFaces = m_pPMesh->GetMaxFaces();
	m_pPMesh->SetNumFaces(maxFaces);//����ԭʼ����ĸ���

	return S_OK;
}

//��������
bool CMesh::SetTexture(const char *TextureFile,int flag)
{
	if(FAILED(D3DXCreateTextureFromFile(m_pD3DDevice,
		TextureFile,
		&m_pMeshTextures[flag])))
	{
		return false;
	}

	return true;
}


void CMesh::Render()
{
	//����alpha�ںϵ�����
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	//��ģ���еĸ����Ӽ���Ⱦ����
	for(int i = 0 ; i < m_dwNumMaterials; i++ )
	{
		m_pD3DDevice->SetMaterial( &m_pMeshMaterials[i] );
		if (m_pMeshTextures[i]!=NULL)
		{
			m_pD3DDevice->SetTexture(0,m_pMeshTextures[i]);
		}
		
		m_pPMesh->DrawSubset(i);  
	}
}



