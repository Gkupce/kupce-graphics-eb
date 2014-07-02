#include <iostream>

#include "includes\Game.h"
#include "includes\Renderer.h"
#include "includes\Window.h"
#include "includes\Timer.h"
#include "includes\Entity2D.h"
#include "includes\Importer.h"

Stu::Engine::Game::Game()
{
	mpoWindow = NULL;
	mpoRenderer = NULL;
	mpoTimer = NULL;
	mpoImporter = NULL;
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
	
	mpoImporter = new Importer(this);
	if(!mpoImporter)
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
	
	for(unsigned int i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if((moDrawUpdateObjs.at(i))->IsAddedToDrawables())
			(moDrawUpdateObjs.at(i))->Draw(mpoRenderer);
		if((moDrawUpdateObjs.at(i))->IsUpdateable())
			(moDrawUpdateObjs.at(i))->Update(this);
	}
	
	mpoRenderer->EndFrame();

	return false;
}
bool Stu::Engine::Game::ShutDown()
{
	bool bError = false;
	if(mpoImporter)
	{
		delete mpoImporter;
		mpoImporter = NULL;
	}
	
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
	if(!entity->IsUpdateable())//it's not already there
		moDrawUpdateObjs.push_back(entity);
	entity->SetAddedToDrawables(true);
}

void Stu::Engine::Game::RemoveFromDrawables(Entity2D* entity)
{
	unsigned int i;

	if(!entity->IsAddedToDrawables()) return;//is not added to drawables, don't even check
	if(entity->IsUpdateable())
	{//it should stay
		entity->SetAddedToDrawables(false);
		return;
	}

	for(i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if(moDrawUpdateObjs.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moDrawUpdateObjs.size()) return;

	moDrawUpdateObjs.erase(moDrawUpdateObjs.begin() + i);

	entity->SetAddedToDrawables(false);
}

void Stu::Engine::Game::AddToUpdateables(Entity2D* entity)
{
	if(!entity->IsAddedToDrawables())//it's not already there
		moDrawUpdateObjs.push_back(entity);
	entity->SetUpdateable(true);
}

void Stu::Engine::Game::RemoveFromUpdateables(Entity2D* entity)
{
	unsigned int i;

	if(!entity->IsUpdateable()) return;//is not added to drawables, don't even check
	if(entity->IsAddedToDrawables())
	{//it should stay
		entity->SetUpdateable(false);
		return;
	}

	for(i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if(moDrawUpdateObjs.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moDrawUpdateObjs.size()) return;

	moDrawUpdateObjs.erase(moDrawUpdateObjs.begin() + i);

	entity->SetUpdateable(false);
}