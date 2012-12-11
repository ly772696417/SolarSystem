#pragma once
#include <iostream>

#include<Windows.h>

//D3DÍ·ÎÄ¼þ
#include<d3d9.h>
#include<d3dx9.h>

#include<dinput.h>
#include<d3dx9core.h>

//D3D lib¿â
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

//Windows lib¿â
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

#include "Debug.h"

#define KEYDOWN(vk_code)  ((GetAsyncKeyState(vk_code) & 0x8000)? 1 : 0)
#define KEYUP(vk_code)    ((GetAsyncKeyState(vk_code) & 0x8000)? 0 : 1)

#define DINPUT_BUFFERSIZE 16

typedef struct  MouseState
{
	bool left;
	bool right;
	POINT pos;
}MSTATE,*PMSTATE;

struct CKeyControl
{
	unsigned int m_Up;
	unsigned int m_Down;
	unsigned int m_Left;
	unsigned int m_Right;
};

struct BoundingBox//AABB
{
    D3DXVECTOR3 _min;
	D3DXVECTOR3 _max;
};

struct BoundingSphere
{
	D3DXVECTOR3 _center;
	float _radius;
};

template <class COM>
void Release(COM t){
	if (t)
	{
		t->Release();
		t = NULL;
	}
}

template <class POINT>
void Delete(POINT t){
	if (t)
	{
		delete t;
		t = NULL;
	}
}












