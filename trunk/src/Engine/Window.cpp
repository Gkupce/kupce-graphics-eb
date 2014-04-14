#include "includes\Window.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

Stu::Engine::Window::Window(HINSTANCE hInstance): 
	mhtInstance(hInstance), 
	mhtWin(NULL)
{
	
}

Stu::Engine::Window::~Window()
{
	DestroyWindow(mhtWin);
}

bool Stu::Engine::Window::WindowCreate(unsigned int uiWidth, unsigned int uiHeight)
{
	WNDCLASS oWC;

	//set window class values in 0
	memset(static_cast<void *> (&oWC), 0, sizeof(WNDCLASS));
	
	oWC.style = CS_HREDRAW | CS_VREDRAW;
	oWC.lpfnWndProc = (WNDPROC) WndProc;
	oWC.hInstance = mhtInstance;
	oWC.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	oWC.lpszClassName = "Engine EB";

	//try registering window class
	if(!RegisterClass(&oWC))
		return true;

	//create the window
	mhtWin = CreateWindow("Engine EB",
						"Engine EB v0.1",
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						uiWidth + 8,
						uiHeight + 30,
						NULL,
						NULL,
						mhtInstance,
						NULL
	);

	if (!mhtWin)
		return true;

	ShowWindow(mhtWin,SW_SHOW);
	UpdateWindow(mhtWin);

	return false;
}

//--------------------------------------------------------------------------------
//Windows process
LRESULT CALLBACK WndProc(HWND htWnd, UINT uiMessage, 
						 WPARAM wParam, LPARAM lParam)

{
	switch (uiMessage) {

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
			ValidateRect(htWnd, NULL);
			break;
	}
	return DefWindowProc(htWnd, uiMessage, wParam, lParam);
}
//--------------------------------------------------------------------------------