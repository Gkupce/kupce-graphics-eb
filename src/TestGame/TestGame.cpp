//system includes
#include <stdio.h>
#include <random>
#include <time.h>
//engine includes
#include <Timer.h>
#include <Window.h>
#include <Triangle.h>
#include <Square.h>
#include <Circle.h>
#include <Sprite.h>
#include <Importer.h>

#include "TestGame.h"

bool TestGame::OnStartUp()
{
	shape = NULL;
	

	if(GetImporter()->LoadResource("../res/TinkRun.xml"))
	{
		return true;
	}
	sprite = NULL;
	sprite = new Stu::Engine::Sprite();
	if(!sprite)
	{
		return true;
	}
	sprite2 = NULL;
	sprite2 = new Stu::Engine::Sprite();
	if(!sprite2)
	{
		return true;
	}

	sprite2->Clone(GetImporter()->GetSprite("TinkRun1"));
	sprite->Clone(GetImporter()->GetSprite("TinkRunning"));
	
	sprite->SetPosition(150,150, 0);
	sprite->SetScale(50,50,1);
	
	sprite2->SetPosition(250,250, 0);
	sprite2->SetScale(50,50,1);

	shape = new Stu::Engine::Circle(100);
	if(!shape)
	{
		return true;
	}
	Stu::Engine::Vector3 scale(50,50,1);
	Stu::Engine::Vector3 position(10,10,0);
	shape->SetScale(scale);
	shape->SetPosition(position);
	shape->SetColor(255,255,0,0);

	AddToDrawables(shape);

	AddToDrawables(sprite2);

	AddToDrawables(sprite);
	AddToUpdateables(sprite);
	
	this->SetClearColor(0xff229922);

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
	
	Stu::Engine::Vector3 rotation = shape->GetRotation();
	rotation.z += 0.05f;
	rotation.y += 0.02f;
	rotation.x += 0.08f;
	shape->SetRotation(rotation);
	
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
	if(sprite2)
	{
		RemoveFromDrawables(sprite2);
		delete sprite2;
		sprite2 = NULL;
	}
	if(shape)
	{
		RemoveFromDrawables(shape);
		RemoveFromUpdateables(shape);
		delete shape;
		shape = NULL;
	}
	if(sprite)
	{
		RemoveFromDrawables(sprite);
		delete sprite;
		sprite = NULL;
	}

	return false;
}
