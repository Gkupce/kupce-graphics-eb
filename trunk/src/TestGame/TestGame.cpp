//system includes
#include <stdio.h>
#include <random>
#include <time.h>
//engine includes
#include <Timer.h>
#include <Window.h>
#include <Shape.h>

#include "TestGame.h"

bool TestGame::OnStartUp()
{
	shape = NULL;
	shape = new Stu::Engine::Shape();
	if(!shape)
	{
		return true;
	}
	Stu::Engine::Vector3 scale(50,50,50);
	Stu::Engine::Vector3 position(150,150,1);
	shape->SetScale(scale);
	shape->SetPosition(position);

	srand(clock());
	return false;
}

bool TestGame::OnLoop()
{
	char* title = NULL;
	title = new char[25];
	if(title)
	{
		sprintf(title, "FPS: %.2f",this->GetTimer()->GetFPS());
		this->GetWindow()->SetTitle(title);
		delete title;
	}
	else
	{
		return true;
	}
	shape->Draw(this->GetRenderer());
	/*
	unsigned long clearColor = ((unsigned long)(((float)rand()/RAND_MAX) * 0xffffffL)) | 0xff000000L;//this->GetClearColor();
	clearColor++;
	if(clearColor >= 0xffffffff)
	{
		clearColor = 0xff000000;
	}
	this->SetClearColor(clearColor);
	/**/
	return false;
}

bool TestGame::OnShutDown()
{
	if(shape)
	{
		delete shape;
		shape = NULL;
	}
	return false;
}
