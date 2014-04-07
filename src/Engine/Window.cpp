#include "includes\Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Stu::Engine::Window::Window(HINSTANCE hInstance): 
	mhInstance(hInstance), 
	mhWin(NULL)
{
	
}

Stu::Engine::Window::~Window()
{
	DestroyWindow(mhWin);
}

bool Stu::Engine::Window::WindowCreate(unsigned int uiWidth, unsigned int uiHeight)
{
	WNDCLASS oWC;

	//set window class values in 0
	memset(static_cast<void *> (&oWC), 0, sizeof(WNDCLASS));
	
	oWC.style = CS_HREDRAW | CS_VREDRAW;
	oWC.lpfnWndProc = (WNDPROC) WndProc;
	oWC.hInstance = mhInstance;
	oWC.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	oWC.lpszClassName = "Engine EB";

	//try registering window class
	if(!RegisterClass(&oWC))
		return true;

	//creo la ventana
	mhWin = CreateWindow("Engine EB",
						"Engine EB v0.1",
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						uiWidth + 8,
						uiHeight + 30,
						NULL,
						NULL,
						mhInstance,
						NULL
	);

	if (!mhWin)
		return true;

	ShowWindow(mhWin,SW_SHOW);
	UpdateWindow(mhWin);

	return false;
}

//--------------------------------------------------------------------------------
//Windows process
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, 
						 WPARAM wParam, LPARAM lParam)

{
	switch (message) {

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			ValidateRect(hWnd, NULL);
			break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
//--------------------------------------------------------------------------------