#include <iostream>
#include "Core/AuUI.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    AuUI::Window WindowA;
    WindowA.Create(AuUI::WindowData(300, 300, 400, 400, L"test123", L"WindowClassName1"), WindowProc, hInstance, hPrevInstance, lpCmdLine, nCmdShow);


    MSG msg;
	while (!WindowA.GetBreakLoop())
	{
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
               WindowA.SetBreakLoop(true);
		}

        if (WindowA.GetBreakLoop())
			break;



	}

    WindowA.Destroy();

    return 0;
}

