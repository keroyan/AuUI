#include <iostream>
#include <Windows.h>
#include <windowsx.h>
#include <d3d9.h>

#pragma comment(lib, "d3d9.lib")

LPDIRECT3D9 pD3D;
LPDIRECT3DDEVICE9 pD3Ddevice;
D3DPRESENT_PARAMETERS d3dpp {};

bool initializeD3D(HWND hWnd);
void cleanD3D(void);

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass1";


	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(NULL, L"WindowClass1", L"Test 1", WS_OVERLAPPEDWINDOW, 300, 300, 500, 500, NULL, NULL, hInstance, NULL);
	
	if (!initializeD3D(hWnd)) 
	{
		cleanD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	bool breakLoop = false;

	MSG msg;
	while (!breakLoop)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				breakLoop = true;
		}

		if (breakLoop)
			break;

	}

	cleanD3D();
	DestroyWindow(hWnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{
	case WM_SIZE:
	{
		if (pD3Ddevice != NULL && wParam != SIZE_MINIMIZED) 
		{
			d3dpp.BackBufferWidth = LOWORD(lParam);
			d3dpp.BackBufferHeight = HIWORD(lParam);
		}
	} break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


bool initializeD3D(HWND hWnd) 
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.hDeviceWindow = hWnd;

	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pD3Ddevice) < 0)
		return false;

	return true;
}

void cleanD3D(void) 
{
	if (pD3Ddevice)
		pD3Ddevice->Release(), pD3Ddevice = NULL;

	if (pD3D)
		pD3D->Release(), pD3D = NULL;
}