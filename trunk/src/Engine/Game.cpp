#include <iostream>

#include "includes\Game.h"
#include "includes\Renderer.h"
#include "includes\Window.h"
#include "includes\Timer.h"
#include "includes\Entity.h"
#include "includes\Importer.h"
#include "includes\Scene.h"
#include "includes\Camera.h"

#include "includes\DirectInput.h"

Stu::Engine::Game::Game()
{
	mpoWindow = NULL;
	mpoRenderer = NULL;
	mpoTimer = NULL;
	mpoImporter = NULL;
	mpoInput = NULL;
	mpoBaseNode = NULL;
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
	
	mpoBaseNode = new Node();
	if(!mpoBaseNode)
	{
		return true;
	}

	mpoImporter = new Importer(this);
	if(!mpoImporter)
	{
		return true;
	}

	mpoInput = new DirectInput(htInstance, mpoWindow->GetWindowHandle());
	if(!mpoInput)
	{
		return true;
	}

	if(!mpoInput->init())
	{//Not mine, conditions inverted
		return true;
	}
	mpoInput->acquire();

	mpoTimer = new Timer();
	if(!mpoTimer)
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
	mpoInput->reacquire();
	mpoTimer->Measure();
	
	if(OnLoop())
	{
		return true;
	}

	mpoBaseNode->UpdateHierarchy(mpoTimer->GetDT());

	mpoRenderer->StartFrame();
	
	mpoBaseNode->DrawHierarchy(mpoRenderer);

	//LEGACY someday
	Camera::GetCamera()->Update(mpoRenderer);

	mpoRenderer->EndFrame();

	return false;
}
bool Stu::Engine::Game::ShutDown()
{
	bool bError = false;
	Camera::DeleteCamera();
	if(OnShutDown())
	{
		bError = true;
	}
	
	if(mpoImporter)
	{
		delete mpoImporter;
		mpoImporter = NULL;
	}
	
	if(mpoBaseNode)
	{
		delete mpoBaseNode;
		mpoBaseNode = NULL;
	}

	if(mpoTimer)
	{
		delete mpoTimer;
		mpoTimer = NULL;
	}

	if(mpoInput)
	{
		mpoInput->deinit();
		delete mpoInput;
		mpoInput = NULL;
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

void Stu::Engine::Game::AddToDrawables(Scene* entity)
{
	mpoBaseNode->AddChild(entity);
	entity->SetAddedToDrawables(true, mpoRenderer);
}

void Stu::Engine::Game::RemoveFromDrawables(Scene* entity)
{
	unsigned int i;

	if(!entity->IsDrawable()) return;//should not be added to drawables, don't even check
	for(i = 0; i < moDrawScenes.size(); i++)
	{
		if(moDrawScenes.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moDrawScenes.size()) return;

	moDrawScenes.erase(moDrawScenes.begin() + i);

	entity->SetAddedToDrawables(false, mpoRenderer);
}

void Stu::Engine::Game::AddToUpdateables(Scene* entity)
{
	if(!entity->IsUpdateable())//it's not already there
		moUpdateScenes.push_back(entity);
	entity->SetUpdateable(true);
}

void Stu::Engine::Game::RemoveFromUpdateables(Scene* entity)
{
	unsigned int i;

	if(!entity->IsUpdateable()) return;//is not added to drawables, don't even check
	
	for(i = 0; i < moUpdateScenes.size(); i++)
	{
		if(moUpdateScenes.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moUpdateScenes.size()) return;

	moUpdateScenes.erase(moUpdateScenes.begin() + i);

	entity->SetUpdateable(false);
}

Input* Stu::Engine::Game::GetInput()
{
	return mpoInput;
}