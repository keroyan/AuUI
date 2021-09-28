#include <iostream>
#include <Windows.h>
#include <windowsx.h>


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

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	while (TRUE) 
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;


	}

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	switch (message) 
	{

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	} break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
