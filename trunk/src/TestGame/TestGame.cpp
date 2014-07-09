//system includes
#include <stdio.h>
#include <random>
#include <time.h>
#include <iostream>
//engine includes
#include <Timer.h>
#include <Window.h>
#include <Triangle.h>
#include <Square.h>
#include <Circle.h>
#include <Sprite.h>
#include <Importer.h>
#include <Input.h>

#include "TestGame.h"

#define UP_ARROW 200
#define DOWN_ARROW 208
#define LEFT_ARROW 203
#define RIGHT_ARROW 205

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
	
	//------------------------------------------------------------------------------
	Stu::Engine::Vector3 shapeMove(0,0,0);
	if(GetInput()->getKeyDown(UP_ARROW))
	{
		Stu::Engine::Vector3 up(0,1,0);
		shapeMove += up * GetTimer()->GetDT();
	}
	if(GetInput()->getKeyDown(DOWN_ARROW))
	{
		Stu::Engine::Vector3 down(0,-1,0);
		shapeMove += down * GetTimer()->GetDT();
	}
	if(GetInput()->getKeyDown(LEFT_ARROW))
	{
		Stu::Engine::Vector3 left(1,0,0);
		shapeMove += left * GetTimer()->GetDT();
	}
	if(GetInput()->getKeyDown(RIGHT_ARROW))
	{
		Stu::Engine::Vector3 right(-1,0,0);
		shapeMove += right * GetTimer()->GetDT();
	}
	shape->SetPosition(shape->GetPosition() + shapeMove);
	//------------------------------------------------------------------------------

	//circle rotations
	/*Stu::Engine::Vector3 rotation = shape->GetRotation();
	rotation.z += 0.05f;
	rotation.y += 0.02f;
	rotation.x += 0.08f;
	shape->SetRotation(rotation);*/
	
	//Search for keys
	/*for(int i = 0; i<255;i++)
	{
		if(GetInput()->getKeyDown(i))
		{
			std::cout << i << "\n";
		}
	}*/
	
	//Flashing colors
	/*unsigned long clearColor = ((unsigned long)(((float)rand()/RAND_MAX) * 0xffffffL)) | 0xff000000L;//this->GetClearColor();
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
