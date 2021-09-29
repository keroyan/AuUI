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

		LPDIRECT3D9 pD3D;
		LPDIRECT3DDEVICE9 pD3Ddevice;
		D3DPRESENT_PARAMETERS D3Dpp{};
		LPDIRECT3DVERTEXBUFFER9 v_buffer;

		bool Create(const WindowData& wData, WNDPROC lpfnWndProc, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
		void Destroy();

		bool GetBreakLoop() { return breakLoop; } const
		void SetBreakLoop(const bool& v) { breakLoop = v; }

	private:
		HWND hWnd;
		WNDCLASSEX wc;

		bool initializeD3D(HWND hWnd);
		void cleanD3D(void);

		bool breakLoop = false;
	};

	class AuVec2 
	{
	public:
		float x, y;
		AuVec2() { x = y = 0.0f; }
		AuVec2(float x, float y) :
			x(x), y(y)
		{}

		void operator+(const AuVec2& vec) { x += vec.x; y += vec.y; }
		void operator-(const AuVec2& vec) { x -= vec.x; y -= vec.y; }
		void operator+=(const AuVec2& vec) { x += vec.x; y += vec.y; }
	};
}