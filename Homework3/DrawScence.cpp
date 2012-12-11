#include "DrawScence.h"

CDrawScence::CDrawScence(LPDIRECT3DDEVICE9 pD3DDevice)
{
	m_pD3DDevice = pD3DDevice;
	globalScale = 1.0;
}


CDrawScence::~CDrawScence(void)
{
}

void CDrawScence::Init(HWND hWnd , HINSTANCE hInstance){
	m_GameInput.InitInput(hWnd,hInstance);

	m_pSkyBox = new CSkyBox(m_pD3DDevice);
	m_pSkyBox->InitSkyBox(8.0f);
	m_pSkyBox->SetTexture("Image\\SkyBoxImage\\right.jpg",0);
	m_pSkyBox->SetTexture("Image\\SkyBoxImage\\left.jpg",1);
	m_pSkyBox->SetTexture("Image\\SkyBoxImage\\top.jpg",2);
	m_pSkyBox->SetTexture("Image\\SkyBoxImage\\bottom.jpg",3);
	m_pSkyBox->SetTexture("Image\\SkyBoxImage\\front.jpg",4);
	m_pSkyBox->SetTexture("Image\\SkyBoxImage\\back.jpg",5);

	m_pLight = new CD3DLight(m_pD3DDevice);
	/* 
	//在程序中画球
	sun = new CSphereMesh(m_pD3DDevice);
	sun->SetTexture("Image\\DrawSphereImage\\sun.jpg");
	earth = new CSphereMesh(m_pD3DDevice);
	earth->SetTexture("Image\\DrawSphereImage\\earth.jpg");
	moon = new CSphereMesh(m_pD3DDevice);
	moon->SetTexture("Image\\DrawSphereImage\\moon.jpg");
	*/

	Sun = new CMesh(m_pD3DDevice);
	Mercury = new CMesh(m_pD3DDevice);
	Vennus = new CMesh(m_pD3DDevice);
	Earth = new CMesh(m_pD3DDevice);
	Mars = new CMesh(m_pD3DDevice);
	Jupiter = new CMesh(m_pD3DDevice);
	Saturn = new CMesh(m_pD3DDevice);
	Uranus = new CMesh(m_pD3DDevice);
	Neptune = new CMesh(m_pD3DDevice);
	Moon = new CMesh(m_pD3DDevice);

	MercuryRingLine = new CRingLine(m_pD3DDevice,2000.0f * globalScale);
	VennusRingLine = new CRingLine(m_pD3DDevice,3600.0f * globalScale);
	EarthRingLine = new CRingLine(m_pD3DDevice,5000.0f * globalScale);
	MarsRingLine = new CRingLine(m_pD3DDevice,8000.0f * globalScale);
	JupiterRingLine = new CRingLine(m_pD3DDevice,16000.0f * globalScale);
	SaturnRingLine = new CRingLine(m_pD3DDevice,20000.0f * globalScale);
	UranusRingLine = new CRingLine(m_pD3DDevice,25000.0f * globalScale);
	NeptuneRingLine = new CRingLine(m_pD3DDevice,28000.0f * globalScale);
	MoonRingLine = new CRingLine(m_pD3DDevice,400.0f * globalScale);

	InitMesh();
	InitRingLine();
}

void CDrawScence::InitMesh(){
	/*
	sun->InitMesh();
	earth->InitMesh();
	moon->InitMesh();
	*/

	Sun->InitMesh("sun.X",1);

	Mercury->InitMesh("Mercury.X",0);
	Vennus->InitMesh("Vennus.X",0);
	Earth->InitMesh("Earth.X",0);
	Mars->InitMesh("Mars.X",0);
	Jupiter->InitMesh("Jupiter.X",0);
	Saturn->InitMesh("Saturn.X",0);
	Uranus->InitMesh("Uranus.X",0);
	Neptune->InitMesh("Neptune.X",0);
	Moon->InitMesh("Moon.X",0);
}

void CDrawScence::InitRingLine(){
	MercuryRingLine->InitVB();
	VennusRingLine->InitVB();
	EarthRingLine->InitVB();
	MarsRingLine->InitVB();
	JupiterRingLine->InitVB();
	SaturnRingLine->InitVB();
	UranusRingLine->InitVB();
	NeptuneRingLine->InitVB();
	MoonRingLine->InitVB();
}

void CDrawScence::Render(){
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pD3DDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);

	SetInput();
	m_Camera.ProcInput(&m_GameInput);
	
	SetupMatrice();
	SetItem();

	m_pSkyBox->Render(m_Camera.g_vPos);
	m_pLight->SetLight(D3DXVECTOR3(0.0f,0.0f,0.0f));

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);

	MercuryRingLine->Render();
	VennusRingLine->Render();
	EarthRingLine->Render();
	MarsRingLine->Render();
	JupiterRingLine->Render();
	SaturnRingLine->Render();
	UranusRingLine->Render();
	NeptuneRingLine->Render();

	/*
	sun->SetMaterial();
	Rotation_Sun();
	sun->Render();

	earth->SetMaterial();
	PlanetRotate(4.0,500.0,1000.0,1.0);
	earth->Render();

	moon->SetMaterial();
	Rotation_Moon();
	moon->Render();
	*/

	Rotation_Sun(0.2f * globalScale);
	Sun->Render();

	Rotation_Planet(2000.0f * globalScale,10000.0f , 8000.0f, 2.0f * globalScale);
	//Rotation_Planet(-58000,870,5.79,0.206,-7);
	Mercury->Render();
	
	Rotation_Planet(3600.0f * globalScale,5000.0f ,-13000.0f, 2.0f * globalScale);
	//Rotation_Planet(243000,-2240,10.82,0.007,3.4);
	Vennus->Render();
	
	Rotation_Planet(5000.0f * globalScale, 8000.0f,18000.0f, 2.0f * globalScale);
	//Rotation_Planet(-1000,3650,14.96,0.0167,2.4);
	MoonRingLine->Render();
	Earth->Render();
	
	Rotation_Moon(2.0f * globalScale);
	Moon->Render();
	
	Rotation_Planet(8000.0f * globalScale, 6000.0f,20000.0f, 2.0f * globalScale);
	//Rotation_Planet(-1000,6860,22.79,0.093,1.8);
	Mars->Render();

	Rotation_Planet(16000.0f * globalScale,8000.0f ,30000.0f, 2.0f * globalScale);
	//Rotation_Planet(-370,43280,77.83,0.048,-1.3);
	Jupiter->Render();
	
	Rotation_Planet(20000.0f * globalScale,10000.0f ,40000.0f, 2.0f * globalScale);
	//Rotation_Planet(-430,107670,142.94,0.055,2.5);
	Saturn->Render();
	
	Rotation_Planet(25000.0f * globalScale, 10000.0f,50000.0f, 2.0f * globalScale);
	//Rotation_Planet(10000,306600,287.09,0.05,-0.8);
	Uranus->Render();

	Rotation_Planet(28000.0f * globalScale,8000.0f ,60000.0f, 2.0f * globalScale);
	//Rotation_Planet(-630,601520,450.40,0.01,1.8);
	Neptune->Render();

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld );

}

void CDrawScence::SetupMatrice()
{
	D3DXMATRIX matView;
	m_Camera.getViewMatrix(&matView);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection, D3DX_PI/3, (GetSystemMetrics(SM_CXSCREEN)*1.0f)/GetSystemMetrics(SM_CYSCREEN), 
		0.001f, 100000.0f );
    m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProjection);

}

void CDrawScence::SetInput(){
	m_GameInput.ReadMouse();
}

void CDrawScence::SetItem(){
	if(KEYDOWN('1')){
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	}
	if(KEYDOWN('2')){
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	}
	if(KEYDOWN('3')){
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_POINT);
	}
}

void CDrawScence::Rotation_Sun(float scale){
	D3DXMATRIX matWorld,matTrans,matRotate,matScale;
	D3DXMatrixIdentity(&matWorld);

	D3DXMatrixScaling(&matScale,scale,scale,scale);
	D3DXMatrixTranslation(&matTrans,0,0,0);
	D3DXVECTOR3 vextor3 = D3DXVECTOR3(0,1,0);
	D3DXMatrixRotationAxis(&matRotate,&vextor3,timeGetTime()/10000.0f);
	matWorld =  matWorld * matScale * matRotate * matTrans ;
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
}


void CDrawScence::Rotation_Moon(float scale){
	D3DXMATRIX matWorld,matTransEarth,matTransMoon,matRotateEarth,matRotateMoon,matScale;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale,scale,scale,scale);
	D3DXMatrixTranslation(&matTransMoon,0.0f,0.0f,400.0f * globalScale);
	D3DXVECTOR3 vector3Y = D3DXVECTOR3(0,1,0);
	D3DXMatrixRotationAxis(&matRotateMoon,&vector3Y,-(timeGetTime()/300.0f));

	matWorld = matWorld * matScale * matTransMoon * matRotateMoon * globalMat;
	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
	
}


void CDrawScence::Rotation_Planet(float r,float autoRate,float revoRate,float scale){
	D3DXMATRIX matWorld,matTrans,matRotate_auto,matRotate_revo,matScale;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale,scale,scale,scale);
	D3DXMatrixTranslation(&matTrans,0,0,r);
	D3DXVECTOR3 vector3Y = D3DXVECTOR3(0,1,0);
	D3DXMatrixRotationAxis(&matRotate_auto,&vector3Y,timeGetTime()/autoRate);//自转
	D3DXMatrixRotationAxis(&matRotate_revo,&vector3Y,timeGetTime()/revoRate);//公转

	matWorld = matWorld * matScale * matRotate_auto * matTrans * matRotate_revo;
	globalMat = matWorld;

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWorld);
}


/*
void CDrawScence::Rotation_Planet(float autoRate ,
													   float revoRate ,
													   float majorAxis, 
													   float eccentricity, 
													   float inclination){
	D3DXMATRIX matWord,matRotateX,matRotate_auto,matRotate_revo,matRotate_inclination,matTran;
	float r;

	r = majorAxis*sqrt(1-pow(eccentricity,2))/sqrt(1-pow(eccentricity,2)*pow(cos(timeGetTime()/revoRate*1.0f),2));

	D3DXMatrixIdentity(&matWord);
	D3DXMatrixIdentity(&matRotateX);
	D3DXMatrixIdentity(&matRotate_auto);
	D3DXMatrixIdentity(&matRotate_revo);
	D3DXMatrixIdentity(&matRotate_inclination);
	D3DXMatrixIdentity(&matTran);

	D3DXMatrixRotationX(&matRotateX,-90.0f/360*D3DX_PI*2);
	D3DXMatrixRotationY(&matRotate_auto,timeGetTime()/autoRate);
	D3DXMatrixTranslation(&matTran,r,0,0);
	D3DXMatrixRotationY(&matRotate_revo,timeGetTime()/revoRate);
	D3DXMatrixRotationX(&matRotate_inclination,inclination * 1.0 /360 * D3DX_PI * 2);

	matWord =  matWord * matRotateX * matRotate_auto * matTran * matRotate_revo * matRotate_inclination;

	m_pD3DDevice->SetTransform(D3DTS_WORLD,&matWord);
}
*/