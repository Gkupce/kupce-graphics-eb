//system includes
#include <stdio.h>
#include <iostream>
#include <random>
#include <time.h>


#include <Triangle.h>
#include <Square.h>
#include <Circle.h>
#include <Sprite.h>
#include <Importer.h>
#include <Input.h>

#include "TestScene2.h"
#include "MyCircle.h"

#define UP_ARROW 200
#define DOWN_ARROW 208
#define LEFT_ARROW 203
#define RIGHT_ARROW 205

#define KP_1 79
#define KP_2 80
#define KP_3 81
#define KP_5 76

const char* meshDir = "../res/3d/bones/bones.xml";
const char* meshName = "Bones";
//const char* meshDir = "../res/3d/tank/tank.xml";
//const char* meshName = "Tank";

TestScene2::TestScene2(Stu::Engine::Importer* importer, Input* input, Stu::Engine::Window* window)
{
	mesh = NULL;
	turret = NULL;
	mpoInput = input;
	mpoWindow = window;

	if(importer->LoadResource(meshDir))
	{
		throw "load error";
	}

	if(importer->LoadResource("../res/TinkRun.xml"))
	{
		throw "load error";
	}

	mesh = importer->GetMesh(meshName)->Clone();
	if(!mesh)
	{//wtf
		throw "error creating mesh";
	}
	
	mesh->SetPosition(0,0,-100);
	//mesh->SetScale(20,20,20);

	/*for(int i = 0; i < mesh->GetChildCount(); i++)
	{
		if(!mesh->GetChild(i)->GetName().compare("Torreta"))
		{
			turret = mesh->GetChild(i);
			break;
		}
	}*/

	AddToDrawables(mesh);
}

TestScene2::~TestScene2()
{
	mpoInput = NULL;
	if(mesh)
	{
		RemoveFromDrawables(mesh);
		RemoveFromUpdateables(mesh);
		delete mesh;
		mesh = NULL;
	}
}

void TestScene2::Update(float deltaTime)
{
	const float shapeSpeed = 2.0f;
	//------------------------------------------------------------------------------
	Stu::Engine::Vector3 shapeMove(0,0,0);
	if(mpoInput->getKeyDown(UP_ARROW))
	{
		Stu::Engine::Vector3 up(0,1,0);
		shapeMove += up * deltaTime;
	}
	if(mpoInput->getKeyDown(DOWN_ARROW))
	{
		Stu::Engine::Vector3 down(0,-1,0);
		shapeMove += down * deltaTime;
	}
	if(mpoInput->getKeyDown(LEFT_ARROW))
	{
		Stu::Engine::Vector3 left(1,0,0);
		shapeMove += left * deltaTime;
	}
	if(mpoInput->getKeyDown(RIGHT_ARROW))
	{
		Stu::Engine::Vector3 right(-1,0,0);
		shapeMove += right * deltaTime;
	}
	if(shapeMove.Magnitude() != 0)
	{
		shapeMove = shapeMove.Normalized() * shapeSpeed;
	}
	mesh->SetPosition(mesh->GetPosition() + shapeMove);
	
	const float shapeSpeed2 = 0.2f;
	shapeMove.SetValues(0,0,0);
	if(mpoInput->getKeyDown(KP_5))
	{
		Stu::Engine::Vector3 up(0,1,0);
		shapeMove += up * deltaTime;
	}
	if(mpoInput->getKeyDown(KP_2))
	{
		Stu::Engine::Vector3 down(0,-1,0);
		shapeMove += down * deltaTime;
	}
	if(mpoInput->getKeyDown(KP_1))
	{
		Stu::Engine::Vector3 left(1,0,0);
		shapeMove += left * deltaTime;
	}
	if(mpoInput->getKeyDown(KP_3))
	{
		Stu::Engine::Vector3 right(-1,0,0);
		shapeMove += right * deltaTime;
	}
	if(shapeMove.Magnitude() != 0)
	{
		shapeMove = shapeMove.Normalized() * shapeSpeed2;
	}
	//turret->SetRotation(turret->GetRotation() + shapeMove);

	char* title = NULL;
	title = new char[40];
	if(title)
	{
		sprintf(title, "POS: x=%.2f y=%.2f z=%.2f",mesh->GetPosition().x,mesh->GetPosition().y,mesh->GetPosition().z);
		mpoWindow->SetTitle(title);
		delete[] title;
	}
	

	/* search for keycodes *
	for(int i = 0; i < 255; i++)
	{
		if(mpoInput->getKeyDown(i))
			std::cout << i << std::endl;
	}
	/**/
}