//System includes
#include <iostream>
#include <Windows.h>
//Engine includes
//Project includes
#include "TestGame.h"

using namespace std;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iShowCmd)
{
	MSG msg;
	bool bQuit = false;
	TestGame* poGame = NULL;
	int errorCode = 0;

	poGame = new TestGame();
	
	if(!poGame)
	{
		//poGame wasn't created
		errorCode = 1;
	}

	if(!errorCode && poGame->StartUp(hInstance))
	{
		//StartUp failed
		errorCode = 1;
	}

	while(!bQuit && !errorCode)
	{
		if(poGame->Loop())
		{
			errorCode = 1;
		}

		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			switch(msg.message)
			{
				// si es un mensaje de salir de la aplicacion
				case WM_QUIT:
					bQuit = true;
					break;

				// si es un mensaje de presionar una tecla
				case WM_KEYDOWN:
				{
					int iKeyCode = (int)msg.wParam;

					switch (iKeyCode)
					{
						// si esa tecla es ESC
						case VK_ESCAPE:
   							bQuit = true;
							break;
					}
					break;
				}
			}
		}
	}
	
	if(poGame)
	{
		poGame->ShutDown();
		delete poGame;
		poGame = NULL;
	}

	return errorCode;
}