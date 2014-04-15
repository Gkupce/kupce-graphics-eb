#include "TestGame.h"

bool TestGame::OnStartUp()
{
	return false;
}

bool TestGame::OnLoop()
{
	/*
	unsigned long clearColor = this->GetClearColor();
	clearColor++;
	if(clearColor >= 0xffffffff)
	{
		clearColor = 0xff000000;
	}
	this->SetClearColor(clearColor);
	/* do not use until the timer class has been created */
	return false;
}

bool TestGame::OnShutDown()
{
	return false;
}
