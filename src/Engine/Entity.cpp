#include "includes\Renderer.h"
#include "includes\Entity.h"

Stu::Engine::Entity::Entity() : Node()
{
	Initialize();
}

Stu::Engine::Entity::Entity(const char* name):Node(name)
{
	Initialize();
}
Stu::Engine::Entity::Entity(std::string name):Node(name)
{
	Initialize();
}

void Stu::Engine::Entity::Initialize()
{
	Vector3 vec(1,1,1);
	SetScale(vec);
}

Stu::Engine::Entity::~Entity()
{}

bool Stu::Engine::Entity::Draw(Renderer* renderer)
{
	this->SetTransformations(renderer);
	/**/
	return false;
}

bool Stu::Engine::Entity::DrawHierarchy(Stu::Engine::Renderer* renderer)
{
	Node::DrawHierarchy(renderer);
	renderer->UnbindMaterial();
//	if(IsAddedToDrawables())
		return Draw(renderer);
	return false;
}