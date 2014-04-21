#include "includes\Renderer.h"
#include "includes\Entity2D.h"

Stu::Engine::Entity2D::Entity2D()
{

}

Stu::Engine::Entity2D::~Entity2D()
{

}

void Stu::Engine::Entity2D::Draw(Renderer* renderer)
{
	renderer->RotateX(rotation.x);
	renderer->RotateY(rotation.y);
	renderer->RotateZ(rotation.z);
	renderer->Scale(scale.x, scale.y);
	renderer->Translate(position.x, position.y, position.z);
}