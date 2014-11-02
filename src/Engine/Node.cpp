#include "includes\Node.h"
#include "includes\Renderer.h"

//Stu::Engine::Node* Stu::Engine::Node::baseNode = NULL;

Stu::Engine::Node::Node()
{
	Initialize();
	moName = "";
}

Stu::Engine::Node::Node(std::string name)
{
	Initialize();
	moName = name;
}

Stu::Engine::Node::Node(const char* name)
{
	Initialize();
	moName = name;
}

void Stu::Engine::Node::Initialize()
{
	mbAddedToDrawables = false;
	mbUpdateable = false;
	mpoParent = NULL;
	moPosition.SetValues(0,0,0);
	moRotation.SetValues(0,0,0);
	moScale.SetValues(1,1,1);
}

Stu::Engine::Node::~Node()
{
	if(mpoParent)
	{
		mpoParent->RemoveChildInt(this);
	}
	while(!moChildren.empty())
	{
		Node* n = moChildren.back();
		moChildren.pop_back();
		n->mpoParent = NULL;
		delete n;
	}
}

void Stu::Engine::Node::SetTransformations(Stu::Engine::Renderer* renderer)
{
	if(mpoParent)
	{
		mpoParent->SetTransformations(renderer);
	}
	else
	{
		renderer->SetMatrixMode(World);
		renderer->LoadIdentity();
	}

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

void Stu::Engine::Node::UpdateHierarchy(float deltaTime)
{
	if(this->IsUpdateable())
	{
		Update(deltaTime);
	}

	for(std::vector<Node*>::iterator it = moChildren.begin(); it != moChildren.end(); it++)
	{
		(*it)->UpdateHierarchy(deltaTime);
	}
}

void Stu::Engine::Node::Clone(const Stu::Engine::Node* original)
{
	SetPosition(original->GetPosition());
	SetRotation(original->GetRotation());
	SetScale(original->GetScale());

	if(GetName().compare("") == 0)//the name of this object is empty
	{
		SetName(original->GetName());
	}

	if(original->moChildren.size() > 0)
	{
		for(std::vector<Node*>::const_iterator it = original->moChildren.begin(); 
			it != original->moChildren.end(); 
			it++)
		{
			Node* child = NULL;
			child = (*it)->Clone();
			if(!child) return;
			
			AddChild(child);
		}
	}
}

Stu::Engine::Node* Stu::Engine::Node::Clone() const
{
	Node* copy = NULL;
	copy = new Node(moName);
	if(!copy) return NULL;
	copy->SetRotation(GetRotation());
	copy->SetPosition(GetPosition());
	copy->SetScale(GetScale());

	if(moChildren.size() > 0)
	{
		for(std::vector<Node*>::const_iterator it = moChildren.begin(); 
			it != moChildren.end();
			it++)
		{
			Node* child = NULL;
			child = (*it)->Clone();
			if(!child) return copy;
			
			copy->AddChild(child);
		}
	}

	return copy;
}