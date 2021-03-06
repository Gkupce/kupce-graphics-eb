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

#include "TestScene3.h"
#include "MyCircle.h"

#define UP_ARROW 200
#define DOWN_ARROW 208
#define LEFT_ARROW 203
#define RIGHT_ARROW 205

#define KP_1 79
#define KP_2 80
#define KP_3 81
#define KP_5 76

const char* meshDir3 = "../res/3d/planeScene/planeScene.xml";
const char* meshName3 = "scene";

TestScene3::TestScene3(Stu::Engine::Importer* importer, Input* input, Stu::Engine::Window* window)
{
	mesh = NULL;
	mpoInput = input;
	mpoWindow = window;

	if(importer->LoadResource(meshDir3))
	{
		throw "load error";
	}

	if(importer->LoadResource("../res/TinkRun.xml"))
	{
		throw "load error";
	}

	mesh = importer->GetMesh(meshName3)->Clone();
	if(!mesh)
	{//wtf
		throw "error creating mesh";
	}
	
	mesh->SetPosition(0,0,-100);
	//mesh->SetScale(20,20,20);

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
	light->SetLightType(Stu::Engine::Spot);
	light->SetRange(200);
	AddLight(light);
}

TestScene3::~TestScene3()
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

void TestScene3::Update(float deltaTime)
{
	char* title = NULL;
	title = new char[40];
	if(title)
	{
		sprintf(title, "POS: x=%.2f y=%.2f z=%.2f",mesh->GetPosition().x,mesh->GetPosition().y,mesh->GetPosition().z);
		mpoWindow->SetTitle(title);
		delete[] title;
	}
}