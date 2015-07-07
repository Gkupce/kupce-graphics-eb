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

#include "ShaderAnimScene.h"
#include "MyCircle.h"

#define UP_ARROW 200
#define DOWN_ARROW 208
#define LEFT_ARROW 203
#define RIGHT_ARROW 205

#define KP_1 79
#define KP_2 80
#define KP_3 81
#define KP_5 76

const char* meshDirSA = "../res/3d/Tiny/Tiny.xml";
const char* meshNameSA = "Tiny";

Stu::Engine::Node* turret;

Stu::Engine::Node* SearchNode(Stu::Engine::Node* base, const char* name)
{
	if(!base->GetName().compare(name))
	{
		return base;
	}
	else
	{
		for(int i = 0; i < base->GetChildCount(); i++)
		{
			Stu::Engine::Node* result = SearchNode(base->GetChild(i), name);
			if(result)
			{
				return result;
			}
		}
		return NULL;
	}
}

ShaderAnimScene::ShaderAnimScene(Stu::Engine::Importer* importer, Input* input, Stu::Engine::Window* window)
{
	mesh = NULL;
	mpoInput = input;
	mpoWindow = window;

	if(importer->LoadResource(meshDirSA))
	{
		throw "load error";
	}

	if(importer->LoadResource("../res/TinkRun.xml"))
	{
		throw "load error";
	}

	mesh = importer->GetMesh(meshNameSA)->Clone();
	if(!mesh)
	{//wtf
		throw "error creating mesh";
	}
	
	mesh->SetPosition(0,0,-100);
	float scale = 0.3f;
	mesh->SetScale(scale, scale, scale);

	AddToDrawables(mesh);

	//--------------------------------
	//Light
	light = NULL;
	light = new Stu::Engine::Light();
	if(!light)
	{
		throw "light fucked";
	}
	Stu::Engine::Color col;
	col.argb = 0x00ffffff;
	light->SetAmbient(col);
	col.argb = 0x00ffffff;
	light->SetSpecular(col);
	col.argb = 0x00ffffff;
	light->SetDiffuse(col);
	Stu::Engine::Vector3 pos(0,0,0);
	light->SetPosition(pos);
	pos.SetValues(1,0,0);
	light->SetAttenuation(pos);
	pos.SetValues(0,0,-10);
	light->SetDirection(pos);
	light->SetSpotFalloff(0.1f);
	light->SetSpotInnerConeRad(0.5f);
	light->SetSpotOuterConeRad(2.0f);
	light->SetLightType(Stu::Engine::Point);
	light->SetRange(200);
	AddLight(light);

	
	turret = mesh;
}



ShaderAnimScene::~ShaderAnimScene()
{
	mpoInput = NULL;
	if(mesh)
	{
		RemoveFromDrawables(mesh);
		RemoveFromUpdateables(mesh);
		delete mesh;
		mesh = NULL;
	}
	
	if(light)
	{
		RemoveLight(light);
		delete light;
		light = NULL;
	}
}

void moveArm(float deltaTime, Input* mpoInput);

void ShaderAnimScene::Update(float deltaTime)
{
	moveArm(deltaTime, mpoInput);

	char* title = NULL;
	title = new char[40];
	if(title)
	{
		sprintf(title, "POS: x=%.2f y=%.2f z=%.2f",mesh->GetPosition().x,mesh->GetPosition().y,mesh->GetPosition().z);
		mpoWindow->SetTitle(title);
		delete[] title;
	}
}

void moveArm(float deltaTime, Input* mpoInput)
{
	if(!turret)
	{
		std::cout << "none"<< std::endl;
		return;
	}
	const float shapeSpeed = 2.0f;
	//------------------------------------------------------------------------------
	Stu::Engine::Vector3 shapeMove(0,0,0);
	const float shapeSpeed2 = 0.2f;
	shapeMove.SetValues(0,0,0);
	if(mpoInput->getKeyDown(KP_5))
	{
		Stu::Engine::Vector3 up(0,1,0);
		shapeMove += up * deltaTime;
		std::cout << "5"<< std::endl;
	}
	if(mpoInput->getKeyDown(KP_2))
	{
		Stu::Engine::Vector3 down(0,-1,0);
		shapeMove += down * deltaTime;
		std::cout << "2"<< std::endl;
	}
	if(mpoInput->getKeyDown(KP_1))
	{
		Stu::Engine::Vector3 left(1,0,0);
		shapeMove += left * deltaTime;
		std::cout << "1"<< std::endl;
	}
	if(mpoInput->getKeyDown(KP_3))
	{
		Stu::Engine::Vector3 right(-1,0,0);
		shapeMove += right * deltaTime;
		std::cout << "3"<< std::endl;
	}
	if(shapeMove.Magnitude() != 0)
	{
		shapeMove = shapeMove.Normalized() * shapeSpeed2;
	}
	turret->SetRotation(turret->GetRotation() + shapeMove);
}