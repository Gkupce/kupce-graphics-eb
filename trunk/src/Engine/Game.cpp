#include <iostream>

#include "includes\Game.h"
#include "includes\Window.h"
#include "includes\Renderer.h"

Stu::Engine::Game::Game()
{
	mpoWindow = NULL;
	mpoRenderer = NULL;
}

Stu::Engine::Game::~Game()
{
	
}

bool Stu::Engine::Game::StartUp(HINSTANCE htInstance)
{
	mpoWindow = new Window(htInstance);
	if(!mpoWindow)
	{
		return true;
	}

	if(mpoWindow->WindowCreate(800,600))
	{
		return true;
	}

	mpoRenderer = new Renderer();
	if(!mpoRenderer)
	{
		return true;
	}

	if(mpoRenderer->Init(mpoWindow))
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

	if(mpoRenderer)
	{
		delete mpoRenderer;
		mpoRenderer = NULL;
	}

	if(mpoWindow)
	{
		delete mpoWindow;
		mpoWindow = NULL;
	}

	return bError;
}