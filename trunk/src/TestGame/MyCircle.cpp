#include <stdio.h>
#include <iostream>

#include "MyCircle.h"

MyCircle::MyCircle():Circle(100)
{
	
}

MyCircle::~MyCircle()
{
	meCollState = Away;
}

void MyCircle::Update(float deltaTime)
{
	Circle::Update(deltaTime);
	if(meCollState == Entered)
	{
		meCollState == Stay;
		std::cout << "MyCircle stay" << std::endl;
	}
	else if(meCollState == Exited)
	{
		meCollState == Away;
		std::cout << "MyCircle Away" << std::endl;
	}
}

void MyCircle::OnCollision(Entity2D* other)
{
	Circle::OnCollision(other);
	if(meCollState == Away)
	{
		meCollState = Entered;
		std::cout << "Entered" << std::endl;
	}
	else
	{
		meCollState = Exited;
		std::cout << "Exited" << std::endl;
	}
}