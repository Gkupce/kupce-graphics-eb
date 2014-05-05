#include <iostream>

#include "includes\Game.h"
#include "includes\Renderer.h"
#include "includes\Window.h"
#include "includes\Timer.h"
#include "includes\Entity2D.h"


Stu::Engine::Game::Game()
{
	mpoWindow = NULL;
	mpoRenderer = NULL;
	mpoTimer = NULL;
	mpoDrawables = NULL;

	mpoDrawables = new std::vector<Entity2D*>();
}

Stu::Engine::Game::~Game()
{
	if(mpoDrawables)
	{
		delete mpoDrawables;
		mpoDrawables = NULL;
	}
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
	
	if(OnLoop())
	{
		return true;
	}

	mpoRenderer->StartFrame();
	
	if(!mpoDrawables)
	{
		mpoRenderer->EndFrame();
		return true;
	}

	for(unsigned int i = 0; i < mpoDrawables->size(); i++)
	{
		(mpoDrawables->at(i))->Draw(mpoRenderer);
	}
	
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

void Stu::Engine::Game::AddToDrawables(Entity2D* entity)
{
	mpoDrawables->push_back(entity);
	entity->SetAddedToDrawables(true);
}

void Stu::Engine::Game::RemoveFromDrawables(Entity2D* entity)
{
	unsigned int i;

	if(!entity->IsAddedToDrawables()) return;//is not added to drawables, don't even check

	for(i = 0; i < mpoDrawables->size(); i++)
	{
		if(mpoDrawables->at(i) == entity)
		{
			break;
		}
	}
	
	if(i == mpoDrawables->size()) return;

	mpoDrawables->erase(mpoDrawables->begin() + i);

	entity->SetAddedToDrawables(false);
}