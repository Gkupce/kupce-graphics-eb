#include "includes\Node.h"
#include "includes\Renderer.h"

Stu::Engine::Node* Stu::Engine::Node::baseNode = NULL;

Stu::Engine::Node::Node()
{
	mbUpdateable = false;
	mpoParent = NULL;
}

Stu::Engine::Node::~Node()
{}

void Stu::Engine::Node::SetTransformations(Stu::Engine::Renderer* renderer)
{
	if(mpoParent)
	{
		mpoParent->SetTransformations(renderer);
	}

	renderer->SetMatrixMode(World);
	renderer->LoadIdentity();
	renderer->Translate(moPosition.x, moPosition.y, moPosition.z);
	
	renderer->RotateX(moRotation.x);
	renderer->RotateY(moRotation.y);
	renderer->RotateZ(moRotation.z);

	renderer->Scale(moScale.x, moScale.y, moScale.z);
}

bool Stu::Engine::Node::CollidesWith(Node* other)
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

bool Stu::Engine::Node::DrawHierarchy(Stu::Engine::Renderer* renderer)
{
	for(std::vector<Node*>::iterator it = moChildren.begin(); it != moChildren.end(); it++)
	{
		(*it)->DrawHierarchy(renderer);
	}

	return false;
}