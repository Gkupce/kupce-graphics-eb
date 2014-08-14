// Engine includes
#include <Vector3.h>
#include <Camera.h>
#include <Input.h>

#include "CamMover.h"

#define KEY_W 17
#define KEY_A 30
#define KEY_S 31
#define KEY_D 32

const float speed = 10.0f;

CamMover::CamMover(Stu::Engine::Camera* camera, Input* input)
{
	this->camera = camera;
	this->input = input;

	camPos = new Stu::Engine::Vector3(0,0,10);
}

CamMover::~CamMover()
{
	delete camPos;
}

void CamMover::OnLoop()
{
	if(input->getKeyDown(KEY_W))
	{//forward
		*camPos += (camera->GetForward() * speed);
	}
	if(input->getKeyDown(KEY_S))
	{//backward
		*camPos -= (camera->GetForward() * speed);
	}
	if(input->getKeyDown(KEY_A))
	{//left
		//camX += 0.01f;
		*camPos += (camera->GetForward().Cross(camera->GetUpward()) * speed);
	}
	if(input->getKeyDown(KEY_D))
	{//right
		*camPos -= (camera->GetForward().Cross(camera->GetUpward()) * speed);
	}
	/*
	if(input->getKeyDown(Input::KEY_SPACE))
	{//up
		//camY -= 0.01f;
		*camPos += (camera->GetUpward() * speed);
	}
	if(input->getKeyDown(Input::KEY_X))
	{//down
		*camPos -= (camera->GetUpward() * speed);
	}
	*/
	if((input->getMouseRelPosX() > 1) || input->getMouseRelPosX() < -1)
	{
		Stu::Engine::Vector3 newForward = camera->GetForward();

		newForward = newForward.RotateAround(camera->GetUpward(), input->getMouseRelPosX()*0.01f);

		camera->SetForward(newForward);
	}/**/

	if((input->getMouseRelPosY() > 1) || input->getMouseRelPosY() < -1)
	{
		Stu::Engine::Vector3 newForward = camera->GetForward();

		newForward = newForward.RotateAround(camera->GetLeft(), input->getMouseRelPosY()*(0.01f));

		camera->SetForward(newForward);
	}

	if(*camPos != camera->GetPosition())
		camera->SetPosition(*camPos);
}