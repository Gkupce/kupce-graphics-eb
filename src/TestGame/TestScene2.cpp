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

TestScene2::TestScene2(Stu::Engine::Importer* importer, Input* input)
{
	shape = NULL;
	shape2 = NULL;
	mpoInput = input;

	if(importer->LoadResource("../res/TinkRun.xml"))
	{
		throw "load error";
	}
	
	shape = new MyCircle();
	if(!shape)
	{
		throw "load error";
	}
	Stu::Engine::Vector3 scale(50,50,1);
	Stu::Engine::Vector3 position(10,10,0);
	shape->SetScale(scale);
	shape->SetPosition(position);
	shape->SetColor(255,255,0,0);


	shape2 = new Stu::Engine::Square();
	if(!shape2)
	{
		throw "load error";
	}
	Stu::Engine::Vector3 scale2(50,50,1);
	Stu::Engine::Vector3 position2(100, -100, 0);
	shape2->SetScale(scale2);
	shape2->SetPosition(position2);
	shape2->SetColor(255,0,0,255);

	shape->AddChild(shape2);

	AddToCollidingGroup("myColl",shape);
	AddToCollidingGroup("myColl",shape2);

	AddToUpdateables(shape);

	shape2->SetAddedToDrawables(true);

	AddToDrawables(shape);
	//AddToDrawables(shape2);
}

TestScene2::~TestScene2()
{
	mpoInput = NULL;
	if(shape)
	{
		RemoveFromDrawables(shape);
		RemoveFromUpdateables(shape);
		delete shape;
		shape = NULL;
	}

	if(shape2)
	{
		RemoveFromDrawables(shape2);
		RemoveFromUpdateables(shape2);
		delete shape2;
		shape2 = NULL;
	}
}

void TestScene2::Update(float deltaTime)
{
	const float shapeSpeed = 20.0f;
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
	shape->SetPosition(shape->GetPosition() + shapeMove);
	
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
		shapeMove = shapeMove.Normalized() * shapeSpeed;
	}
	shape2->SetPosition(shape2->GetPosition() + shapeMove);

	/* search for keycodes *
	for(int i = 0; i < 255; i++)
	{
		if(mpoInput->getKeyDown(i))
			std::cout << i << std::endl;
	}
	/**/
}