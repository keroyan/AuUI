#pragma once
#include <Windows.h>
#include <windowsx.h>

#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

namespace AuUI 
{
	struct WindowData
	{
		int posX = 0,
			posY = 0,
			width = 400,
			height = 400;

		LPCWSTR
			title,
			className;

		WindowData(int posX, int posY, int width, int height, LPCWSTR title, LPCWSTR className) :
			posX(posX), posY(posY), width(width), height(height), title(title), className(className)
		{}
	};

	class Window 
	{
	public:
		bool Create(const WindowData& wData, WNDPROC lpfnWndProc, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
		void Destroy();
		bool GetBreakLoop() { return breakLoop; } const
		void SetBreakLoop(const bool& v) { breakLoop = v; }
	private:
		HWND hWnd;
		WNDCLASSEX wc;
		LPDIRECT3D9 pD3D;
		LPDIRECT3DDEVICE9 pD3Ddevice;
		D3DPRESENT_PARAMETERS d3dpp{};

		bool initializeD3D(HWND hWnd);
		void cleanD3D(void);

		bool breakLoop = false;
	};
}