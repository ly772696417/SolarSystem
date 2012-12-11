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
	//例如，顶点缓冲区，材质集合，纹理集合等Direct3D数据。
	if( FAILED(D3DXLoadMeshFromX( TextureFilePath,
														D3DXMESH_SYSTEMMEM,  //指定生成的多边形网格属性
														m_pD3DDevice,
														&pAdjBuffer,         //存储邻近多边形信息的LPD3DXBUFFER地址
														&pD3DXMtrBuffer,     //存储模型材质的LPD3DXBUFFER地址
														NULL,                //存储模型特效的LPD3DXBUFFER地址
														&m_dwNumMaterials,   //存储模型材质数量的内存地址
														&m_pMesh )))         //存储生成的多边形网格的内存地址
	{
		return E_FAIL;
	}

	D3DXMATERIAL  *d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrBuffer->GetBufferPointer();
	//根据加载材质的组数为材质和纹理分配保存的空间。
	m_pMeshMaterials = new D3DMATERIAL9[m_dwNumMaterials];
	m_pMeshTextures  = new LPDIRECT3DTEXTURE9[m_dwNumMaterials];

	//通过循环来为模型创建纹理
	for( DWORD i = 0; i < m_dwNumMaterials; i++ )
	{   //把模型中的材质放入我们自己分配的材质空间中
		m_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;
		// X中没有环境光Ambient，把慢反射的直给环境光
		m_pMeshMaterials[i].Ambient = m_pMeshMaterials[i].Diffuse;
		if (sunFlag)
		{
			m_pMeshMaterials[i].Emissive = D3DXCOLOR(1,0.7,0.7,1);
		}
		m_pMeshTextures[i] = NULL;  //纹理指针先清空 
		//如果材质对应组有纹理，我们就把纹理创建出来
		if (i<5)
		{
			if( d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0 )
			{    
				//创建纹理，用我们指定的指针指向
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

	//优化网格
	if(FAILED(m_pMesh->OptimizeInplace( 
		D3DXMESHOPT_ATTRSORT |     //根据属性给三角形排序并调整属性表，这将使DrawSubset方法更有效的执行
		D3DXMESHOPT_COMPACT  |     //删除没有用的顶点和索引项
		D3DXMESHOPT_VERTEXCACHE,   //增加顶点缓冲的命中率
		(DWORD*)pAdjBuffer->GetBufferPointer(), //没有优化的Mesh的邻接数组
		(DWORD*)pAdjBuffer->GetBufferPointer(), //输出优化的Mesh的邻接信息的数组
		0, 0)))
	{
		return E_FAIL;
	}

	//生成渐进式网格
	if(FAILED(D3DXGeneratePMesh(m_pMesh,  //输入的普通的Mesh对象
													(DWORD*)pAdjBuffer->GetBufferPointer(),  //Mesh对象的邻接信息
													0, //表示顶点的属性的权。在简化Mesh对象时，
													//权值决定一个顶点被删除的可能性大小。该
													//参数可以设为NULL，这时顶点使用默认的权值
													0,  // 用于决定顶点在简化时被删除的可能性的
													//大小该参数也可设为NULL，
													//这时，顶点默认的权值为1.0f。		                                  
													10,// 在简化Mesh时，顶点或者三角形数的最小个数
													D3DXMESHSIMP_FACE, // 只能取D3DXMESHSIMP枚举类型中的一个值：
													// D3DXMESHSIMP_VERTEX –上一个参数MinValue指顶点数
													// D3DXMESHSIMP_FACE –上一个参数MinValue指三角形数
													&m_pPMesh)))
	{
		return E_FAIL;
	} 
	
	DWORD maxFaces = m_pPMesh->GetMaxFaces();
	m_pPMesh->SetNumFaces(maxFaces);//设置原始的面的个数

	return S_OK;
}

//设置纹理
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
	//设置alpha融合的属性
	m_pD3DDevice->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	//把模型中的各个子集渲染出来
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



