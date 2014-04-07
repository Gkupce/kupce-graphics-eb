#include <iostream>

#include "includes\Game.h"
#include "includes\Window.h"

Stu::Engine::Game::Game()
{
	mpoWindow = NULL;
	
}

Stu::Engine::Game::~Game()
{
	
}

bool Stu::Engine::Game::StartUp(HINSTANCE hInstance)
{
	mpoWindow = new Window(hInstance);
	if(!mpoWindow)
	{
		return true;
	}

	if(mpoWindow->WindowCreate(800,600))
	{
		return true;
	}

	if(OnStartUp())
	{
		return true;
	}

	return false;
}
bool Stu::Engine::Game::Loop()
{
	if(OnLoop())
	{
		return true;
	}

	return false;
}
bool Stu::Engine::Game::ShutDown()
{
	bool bError = false;
	if(OnShutDown())
	{
		bError = true;
	}

	if(mpoWindow)
	{

		delete mpoWindow;
		mpoWindow = NULL;
	}

	return bError;
}