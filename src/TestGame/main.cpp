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
				// the message is for closing the application
				case WM_QUIT:
				case WM_CLOSE:
					bQuit = true;
					break;
				
				// the message is a keypress
				case WM_KEYDOWN:
				{
					int iKeyCode = (int)msg.wParam;

					switch (iKeyCode)
					{
						// the key is ESC
						case VK_ESCAPE:
   							bQuit = true;
							break;
					}
					break;
				}
			}
			//release the message to the wind(ows)
			TranslateMessage(&msg);
			DispatchMessage(&msg);
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