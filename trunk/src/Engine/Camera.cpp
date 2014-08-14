#include <d3d9.h>
#include <d3dx9.h>

#include "includes/Vector3.h"
#include "includes/Renderer.h"
#include "includes/Camera.h"

//TODO bring camera handling from renderer

Stu::Engine::Camera* Stu::Engine::Camera::instance = NULL;

void Stu::Engine::Camera::DeleteCamera()
{
	if(Stu::Engine::Camera::instance)
	{
		delete Stu::Engine::Camera::instance;
	}
}

Stu::Engine::Camera* Stu::Engine::Camera::GetCamera()
{
	if(Stu::Engine::Camera::instance)
	{
		return Stu::Engine::Camera::instance;
	}
	instance = new Camera();
	return instance;
}

Stu::Engine::Camera* Stu::Engine::Camera::GetCamera(float x, float y, float z)
{
	if(Stu::Engine::Camera::instance)
	{
		Stu::Engine::Camera::instance->SetPosition(x,y,z);
		return Stu::Engine::Camera::instance;
	}
	instance = new Camera(x,y,z);
	return instance;
}

void Stu::Engine::Camera::SetPosition(float x, float y, float z)
{
	viewerPos->x = x;
	viewerPos->y = y;
	viewerPos->z = z;
	changed = true;
}

void Stu::Engine::Camera::SetUpward(float x, float y, float z)
{
	viewerUp->x = x;
	viewerUp->y = y;
	viewerUp->z = z;
	changed = true;
}

void Stu::Engine::Camera::SetPosition(Stu::Engine::Vector3 position)
{
	viewerPos->x = position.x;
	viewerPos->y = position.y;
	viewerPos->z = position.z;
	changed = true;
}

void Stu::Engine::Camera::SetUpward(Stu::Engine::Vector3 up)
{
	//TODO
	up = up.Normalized();

	viewerUp->x = up.x;
	viewerUp->y = up.y;
	viewerUp->z = up.z;
	changed = true;
}

void Stu::Engine::Camera::SetForward(Stu::Engine::Vector3 forward)
{
	forward = forward.Normalized();
	/**/
	if(forward == Vector3::FromDXVec(*viewerUp))
	{
		viewerUp->x = -viewerForward->x;
		viewerUp->y = -viewerForward->y;
		viewerUp->z = -viewerForward->z;

		*viewerForward = forward.getD3DVector();
		
		return;
	}

	if(forward == -Vector3::FromDXVec(*viewerUp))
	{
		viewerUp->x = viewerForward->x;
		viewerUp->y = viewerForward->y;
		viewerUp->z = viewerForward->z;

		*viewerForward = forward.getD3DVector();
		
		return;
	}
	/**/
	*viewerForward = forward.getD3DVector();
	
	Vector3 left = GetLeft();
	*viewerUp = forward.Cross(left).Normalized().getD3DVector();
	changed = true;
}

void Stu::Engine::Camera::SetForward(float x, float y, float z)
{
	Vector3 forward(x,y,z);
	forward = forward.Normalized();

	if(forward == Vector3::FromDXVec(*viewerUp))
	{
		viewerUp->x = -viewerForward->x;
		viewerUp->y = -viewerForward->y;
		viewerUp->z = -viewerForward->z;

		*viewerForward = forward.getD3DVector();
		
		return;
	}

	if(forward == -Vector3::FromDXVec(*viewerUp))
	{
		viewerUp->x = viewerForward->x;
		viewerUp->y = viewerForward->y;
		viewerUp->z = viewerForward->z;

		*viewerForward = forward.getD3DVector();
		
		return;
	}

	*viewerForward = forward.getD3DVector();


	Vector3 left = GetLeft();
	*viewerUp = forward.Cross(left).Normalized().getD3DVector();

	changed = true;
}

void Stu::Engine::Camera::Rotate(float x, float y, float z)
{
	rotation->x = x;
	rotation->y = y;
	rotation->z = z;
	changed = true;
}

Stu::Engine::Vector3 Stu::Engine::Camera::GetPosition()
{
	Vector3 pos(*viewerPos);
	return pos;
}

Stu::Engine::Vector3 Stu::Engine::Camera::GetUpward()
{
	Vector3 up(*viewerUp);
	return up;
}

Stu::Engine::Vector3 Stu::Engine::Camera::GetForward()
{
	Vector3 forward(*viewerForward);
	return forward;
}

Stu::Engine::Vector3 Stu::Engine::Camera::GetLeft()
{
	Vector3 Left = Vector3::FromDXVec(*viewerUp).Cross(*viewerForward);
	return Left;
}

Stu::Engine::Camera::Camera(float x, float y, float z)
{
	D3DXMATRIX projectionMatrix;
	viewerPos = new D3DXVECTOR3;
	viewerUp = new D3DXVECTOR3;
	viewerForward = new D3DXVECTOR3;
	viewerMatrix = new D3DXMATRIX;
	rotation = new D3DXVECTOR3;

	ZeroMemory(viewerPos, sizeof(D3DXVECTOR3));
	ZeroMemory(viewerUp, sizeof(D3DXVECTOR3));
	ZeroMemory(viewerForward, sizeof(D3DXVECTOR3));
	ZeroMemory(rotation, sizeof(D3DXVECTOR3));
	viewerUp->y = 1;
	viewerPos->z = 10;
	viewerForward->z = -1;

}

Stu::Engine::Camera::~Camera()
{
	if(viewerPos) delete viewerPos;
	if(viewerUp) delete viewerUp;
	if(viewerForward) delete viewerForward;
	if(viewerMatrix) delete viewerMatrix;
	if(rotation) delete rotation;
}

void Stu::Engine::Camera::Update(Stu::Engine::Renderer* renderer)
{
	if(!changed) return;
	renderer->SetMatrixMode(View);
	renderer->LoadIdentity();
	renderer->Translate(viewerPos->x, viewerPos->y, viewerPos->z);
	renderer->SetViewportPosition(this);
	changed = false;
}