#include <iostream>

#include "includes\Game.h"
#include "includes\Entity2D.h"
#include "includes\Renderer.h"
#include "includes\Window.h"
#include "includes\Timer.h"


Stu::Engine::Game::Game()
{
	mpoWindow = NULL;
	mpoRenderer = NULL;
	mpoTimer = NULL;
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

	mpoTimer = new Timer();
	if(!mpoTimer)
	{
		return true;
	}

	return false;
}
bool Stu::Engine::Game::Loop()
{
	mpoTimer->Measure();
	
	mpoRenderer->StartFrame();

	if(OnLoop())
	{
		return true;
	}

	//
	//if(!mpoDrawables)
	//{
	//	mpoRenderer->EndFrame();
	//	return true;
	//}

	//for(int i = 0; i < mpoDrawables->size(); i++)
	//{
	//	//Entity2d is incoplete type, wtf?
	//	(mpoDrawables->at(i))->Draw(mpoRenderer);
	//}
	//
	mpoRenderer->EndFrame();

	return false;
}
bool Stu::Engine::Game::ShutDown()
{
	bool bError = false;
	if(mpoTimer)
	{
		delete mpoTimer;
		mpoTimer = NULL;
	}

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