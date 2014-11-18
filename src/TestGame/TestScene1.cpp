//system includes
#include <stdio.h>
#include <random>
#include <time.h>
#include <iostream>
#include <Triangle.h>
#include <Square.h>
#include <Circle.h>
#include <Sprite.h>
#include <Importer.h>
#include <Input.h>


#include "TestScene1.h"

const char* tileMapDir = "../res/my tile map.tmx";

TestScene1::TestScene1(Stu::Engine::Importer* importer, Input* input)
{
	mpoInput = input;

	if(importer->LoadResource("../res/TinkRun.xml"))
	{
		throw "load error";
	}
	sprite = NULL;
	sprite = new Stu::Engine::Sprite();
	if(!sprite)
	{
		throw "load error";
	}
	sprite2 = NULL;
	sprite2 = new Stu::Engine::Sprite();
	if(!sprite2)
	{
		throw "load error";
	}

	if(importer->LoadTileMap(tileMapDir))
	{
		throw "load error";
	}

	tilemap = NULL;
	tilemap = new Stu::Engine::Tilemap(); 
	if(!tilemap)
	{
		throw "load error tm";
	}

	tilemap->Clone(importer->GetTileMap(tileMapDir));

	tilemap->SetPosition(0, -50, -50);
	tilemap->SetScale(20,20,1);

	sprite2->Clone(importer->GetSprite("TinkRun1"));
	sprite->Clone(importer->GetSprite("TinkRunning"));
	
	sprite->SetPosition(150,150, 0);
	sprite->SetScale(50,50,1);
	
	sprite2->SetPosition(250,250, 0);
	sprite2->SetScale(50,50,1);

	AddToDrawables(tilemap);
	AddToDrawables(sprite2);

	AddToDrawables(sprite);
	AddToUpdateables(sprite);

	//--------------------------------
	//Light
	light = NULL;
	light = new Stu::Engine::Light();
	if(!light)
	{
		throw "light fucked";
	}
	Stu::Engine::Color col;
	col.argb = 0xff0000ff;
	light->SetAmbient(col);
	col.argb = 0xffff0000;
	light->SetSpecular(col);
	col.argb = 0xff00ff00;
	light->SetDiffuse(col);
	AddLight(light);
	Stu::Engine::Vector3 pos(0,0,0);
	light->SetPosition(pos);
	light->SetLightType(Stu::Engine::Point);
	light->SetRange(20000);
	
}

TestScene1::~TestScene1()
{
	mpoInput = NULL;
	if(sprite2)
	{
		RemoveFromDrawables(sprite2);
		delete sprite2;
		sprite2 = NULL;
	}
	if(sprite)
	{
		RemoveFromDrawables(sprite);
		delete sprite;
		sprite = NULL;
	}
	if(light)
	{
		RemoveLight(light);
		delete light;
		light = NULL;
	}
}