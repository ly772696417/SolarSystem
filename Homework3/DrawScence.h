#pragma once

#include "header.h"
#include "SphereMesh.h"
#include "Mesh.h"
#include "RingLine.h"
#include "SkyBox.h"
#include "D3DLight.h"
#include  "Camera.h"
#include "GameInput.h"

class CDrawScence
{
public:
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	 CCamera m_Camera;
	 GameInput m_GameInput;
	 CSkyBox *m_pSkyBox;
	 CD3DLight *m_pLight;

	 D3DXMATRIX globalMat;
	 float globalScale;

	 //程序中生成球
	CSphereMesh *sun;
	CSphereMesh *earth;
	CSphereMesh *moon;

	//X文件生成球
	CMesh *Sun;
	CMesh *Mercury;
	CMesh *Vennus;
	CMesh *Earth;
	CMesh *Mars;
	CMesh *Jupiter;
	CMesh *Saturn;
	CMesh *Uranus;
	CMesh *Neptune;
	CMesh *Moon;

	CRingLine *MercuryRingLine;
	CRingLine *VennusRingLine;
	CRingLine *EarthRingLine;
	CRingLine *MarsRingLine;
	CRingLine *JupiterRingLine;
	CRingLine *SaturnRingLine;
	CRingLine *UranusRingLine;
	CRingLine *NeptuneRingLine;
	CRingLine *MoonRingLine;

public:
	CDrawScence(LPDIRECT3DDEVICE9  pD3DDevice);
	~CDrawScence(void);

	void Init(HWND hWnd , HINSTANCE hInstance);
	void InitMesh();
	void InitRingLine();

	void SetupMatrice();
	void SetInput();
	void SetItem();

	void Rotation_Sun(float scale);
	void Rotation_Moon(float scale);
	void Rotation_Planet(float r,float autoRate,float revoRate,float scale);
	//void Rotation_Planet(float autoRate ,float revoRate ,float majorAxis, float eccentricity, float inclination);

	void Render();
};

