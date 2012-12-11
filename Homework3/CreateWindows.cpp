#include "header.h"
#include "D3DInit.h"

CD3DInit *d3dInit = new CD3DInit();

long FAR PASCAL WndPro(HWND hWnd,
										UINT message,
										WPARAM wParam,
										LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		case WM_KEYDOWN:
			switch (wParam)
			{
			case VK_ESCAPE:
				PostMessage(hWnd,WM_CLOSE,0,0);
				break;
			default:
				break;
			}
		default:
			break;
	}

	return DefWindowProc(hWnd,message,wParam,lParam);
}

int CALLBACK WinMain(HINSTANCE hInstacne,
									HINSTANCE hPrevInstance,
									LPSTR lpCmdLine,
									int nCmdShow)
{
	MSG msg;
	HWND hWnd;
	WNDCLASS wc;

	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hInstacne;
	wc.lpfnWndProc = WndPro;
	wc.lpszClassName = "solar system";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	hWnd = CreateWindowEx(WS_EX_TOPMOST,
											"solar system",
											"solar system",
											WS_OVERLAPPEDWINDOW,
											0,
											0,
											GetSystemMetrics(SM_CXSCREEN),
											GetSystemMetrics(SM_CYSCREEN),
											NULL,
											NULL,
											hInstacne,
											NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	d3dInit->GameInit(hWnd,hInstacne);

	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	while (true)
	{
		if (PeekMessage(&msg,NULL,0U,0U,PM_REMOVE))
		{
			if (msg.message  == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		else
		{
			d3dInit->Render();
		}
	}

	return 1;
}