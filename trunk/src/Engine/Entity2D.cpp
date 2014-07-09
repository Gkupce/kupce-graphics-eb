#include "includes\Renderer.h"
#include "includes\Entity2D.h"
#include "includes\AABB2D.h"

Stu::Engine::Entity2D::Entity2D()
{
	moScale.x = 1;
	moScale.y = 1;
	moScale.z = 1;
	mbAddedToDrawables = false;
	mbUpdateable = false;
	mpoBoundingBox = NULL;
}

Stu::Engine::Entity2D::~Entity2D()
{
	if(mpoBoundingBox)
	{
		delete mpoBoundingBox;
		mpoBoundingBox = NULL;
	}
}

bool Stu::Engine::Entity2D::Draw(Renderer* renderer)
{
	renderer->SetMatrixMode(World);
	renderer->LoadIdentity();
	renderer->Translate(moPosition.x, moPosition.y, moPosition.z);
	
	renderer->RotateX(moRotation.x);
	renderer->RotateY(moRotation.y);
	renderer->RotateZ(moRotation.z);

	renderer->Scale(moScale.x, moScale.y);
	/**/
	return false;
}

bool Stu::Engine::Entity2D::CreateAABB(Stu::Engine::Vector3 max, Stu::Engine::Vector3 min)
{
	mpoBoundingBox = new AABB2D();
	return (mpoBoundingBox);
}