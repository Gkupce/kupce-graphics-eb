#include "includes\Renderer.h"
#include "includes\Entity2D.h"

Stu::Engine::Entity2D::Entity2D()
{
	moScale.x = 1;
	moScale.y = 1;
	moScale.z = 1;
	mbAddedToDrawables = false;
	mbUpdateable = false;
}

Stu::Engine::Entity2D::~Entity2D()
{}

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

bool Stu::Engine::Entity2D::CollidesWith(Entity2D* other)
{
	Vector3 otherMax(other->moMaxCoord.x * other->moScale.x + other->moPosition.x, 
						other->moMaxCoord.y * other->moScale.y + other->moPosition.y,0);
	Vector3 otherMin(other->moMinCoord.x * other->moScale.x + other->moPosition.x, 
						other->moMinCoord.y * other->moScale.y + other->moPosition.y,0);
	Vector3 thisMax(moMaxCoord.x * moScale.x + moPosition.x, 
						moMaxCoord.y * moScale.y + moPosition.y,0);
	Vector3 thisMin(moMinCoord.x * moScale.x + moPosition.x, 
						moMinCoord.y * moScale.y + moPosition.y,0);

	return !((otherMax.x < thisMin.x) || (thisMax.x < otherMin.x) || (otherMax.y < thisMin.y) || (thisMax.y < otherMin.y));
}
