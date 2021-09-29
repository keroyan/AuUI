#include "AuUI.h"


bool AuUI::Window::Create(const WindowData& wData, WNDPROC lpfnWndProc, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Clearing WC
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// Setting our own settings
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = lpfnWndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = wData.className;

	// Registering wc
	RegisterClassEx(&wc);

	// Creating the window
    hWnd = CreateWindowEx(NULL, wData.className, wData.title, WS_OVERLAPPEDWINDOW, wData.posX, wData.posY, wData.width, wData.height, NULL, NULL, hInstance, NULL);

	// Implementing D3D to the window
	if (!initializeD3D(hWnd))
	{
		cleanD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return false;
	}

	// Showing the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
}

bool AuUI::Window::initializeD3D(HWND hWnd)
{
	pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory(&D3Dpp, sizeof(D3Dpp));
	D3Dpp.Windowed = TRUE;
	D3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	D3Dpp.EnableAutoDepthStencil = TRUE;
	D3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	D3Dpp.AutoDepthStencilFormat = D3DFMT_D16;
	D3Dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	D3Dpp.hDeviceWindow = hWnd;

	if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &D3Dpp, &pD3Ddevice) < 0)
		return false;

	return true;
}

void AuUI::Window::cleanD3D(void)
{
	if (pD3Ddevice)
		pD3Ddevice->Release(), pD3Ddevice = NULL;

	if (pD3D)
		pD3D->Release(), pD3D = NULL;
}

void AuUI::Window::Destroy()
{
	cleanD3D();
	DestroyWindow(hWnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
}

