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
#include <Camera.h>

#include "TestGame.h"
#include "TestScene2.h"
#include "TestScene1.h"

#define UP_ARROW 200
#define DOWN_ARROW 208
#define LEFT_ARROW 203
#define RIGHT_ARROW 205

//#define KEY_
#define KEY_Q 16
#define KEY_W 17
#define KEY_A 30
#define KEY_S 31
#define KEY_E 18
#define KEY_R 19
#define KEY_D 32
#define KEY_F 33


bool TestGame::OnStartUp()
{
	camMover = NULL;
	camMover = new CamMover(Stu::Engine::Camera::GetCamera(), GetInput());
	if(!camMover)
	{
		return true;
	}

	mpoScene2 = NULL;
	mpoScene2 = new TestScene2(GetImporter(),GetInput(), GetWindow());
	if(!mpoScene2)
	{
		return true;
	}

	mpoScene1 = NULL;
	mpoScene1 = new TestScene1(GetImporter(),GetInput());
	if(!mpoScene1)
	{
		return true;
	}

	AddToDrawables(mpoScene2);
	AddToUpdateables(mpoScene2);
	AddToDrawables(mpoScene1);
	AddToUpdateables(mpoScene1);
	
	srand(clock());

	this->SetClearColor(0xff229922);
	return false;
}

bool TestGame::OnLoop()
{
	camMover->OnLoop();

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
	}/**/
	
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
	if(camMover)
	{
		delete camMover;
		camMover = NULL;
	}
	if(mpoScene1)
	{
		delete mpoScene1;
		mpoScene1 = NULL;
	}
	if(mpoScene2)
	{
		delete mpoScene2;
		mpoScene2 = NULL;
	}


	return false;
}
