//System includes
#include <iostream>
#include <Windows.h>

//#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>
//Engine includes
//Project includes
#include "TestGame.h"

using namespace std;

void RedirectIOToConsole();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iShowCmd)
{
	RedirectIOToConsole();
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

// maximum mumber of lines the output console should have
static const WORD MAX_CONSOLE_LINES = 500;


void RedirectIOToConsole()
{
    int hConHandle;
    long lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

// allocate a console for this app
    AllocConsole();

// set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&coninfo);
    coninfo.dwSize.Y = MAX_CONSOLE_LINES;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),coninfo.dwSize);

// redirect unbuffered STDOUT to the console
    lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stdout = *fp;

    setvbuf( stdout, NULL, _IONBF, 0 );

// redirect unbuffered STDIN to the console

    lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

// redirect unbuffered STDERR to the console
    lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

    fp = _fdopen( hConHandle, "w" );

    *stderr = *fp;

    setvbuf( stderr, NULL, _IONBF, 0 );

// make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog
// point to console as well
    ios::sync_with_stdio();
}