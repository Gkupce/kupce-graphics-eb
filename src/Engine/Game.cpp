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
	mpoRenderer->StartFrame();

	if(OnLoop())
	{
		return true;
	}

	mpoRenderer->EndFrame();

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

void Stu::Engine::Game::SetClearColor(unsigned long clearColor)
{
	mpoRenderer->SetClearColor(clearColor);
}

void Stu::Engine::Game::SetClearColor(int a, int r, int g, int b)
{
	mpoRenderer->SetClearColor(a,r,g,b);
}

unsigned long Stu::Engine::Game::GetClearColor()
{
	return mpoRenderer->GetClearColor();
}