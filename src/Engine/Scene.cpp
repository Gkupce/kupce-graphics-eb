#include "includes\Scene.h"
#include "includes\Entity.h"

Stu::Engine::Scene::Scene()
{
	mbIsDrawable = false;
}

Stu::Engine::Scene::~Scene()
{

}

//void Stu::Engine::Scene::Update(float dt)
//{
//	
//	for(unsigned int i = 0; i < moUpdateObjs.size(); i++)
//	{
//		moUpdateObjs.at(i)->Update(dt);
//	}
//
//	CalculateCollisions();
//}


void Stu::Engine::Scene::AddToDrawables(Node* entity)
{
	if(entity->GetParent() != NULL)
	{
		assert(entity->GetParent() != NULL);
		return;
	}
	
	AddChild(entity);
	entity->SetAddedToDrawables(true);
}

void Stu::Engine::Scene::RemoveFromDrawables(Node* entity)
{
	unsigned int i;

	if(!entity->IsAddedToDrawables()) return;//is not added to drawables, don't even check

	for(i = 0; i < moDrawObjs.size(); i++)
	{
		if(moDrawObjs.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moDrawObjs.size()) return;

	moDrawObjs.erase(moDrawObjs.begin() + i);

	entity->SetAddedToDrawables(false);
}

void Stu::Engine::Scene::AddToUpdateables(Node* entity)
{
	if(!entity->IsUpdateable())//it's not already there
	{
		moUpdateObjs.push_back(entity);
		entity->SetUpdateable(true);
	}
}

void Stu::Engine::Scene::RemoveFromUpdateables(Node* entity)
{
	unsigned int i;

	if(!entity->IsUpdateable()) return;//is not added to drawables, don't even check

	for(i = 0; i < moUpdateObjs.size(); i++)
	{
		if(moUpdateObjs.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moUpdateObjs.size()) return;

	moUpdateObjs.erase(moUpdateObjs.begin() + i);

	entity->SetUpdateable(false);
}

void Stu::Engine::Scene::CalculateCollisions()
{
	for(std::map<std::string, std::vector<Entity*>>::iterator it = moCollidingGroups.begin(); 
		it != moCollidingGroups.end(); 
		it++)
	{
		for(int i = 0; i < it->second.size(); i++)
		{
			for(int j = i + 1; j < it->second.size(); j++)
			{
				if(it->second[i]->CollidesWith(it->second[j]))
				{
					it->second[i]->OnCollision(it->second[j]);
					it->second[j]->OnCollision(it->second[i]);
				}
			}
		}
	}
}

void Stu::Engine::Scene::AddToCollidingGroup(std::string group, Entity* entity)
{
	std::map<std::string, std::vector<Entity*>>::iterator it = moCollidingGroups.find(group);

	if(it != moCollidingGroups.end())
	{
		std::vector<Entity*>::iterator it2 = it->second.begin();
		for(; it2 != it->second.end(); it2++)
		{
			
			if(*it2 == entity) return;//it's already there
		}
		if(it2 == it->second.end())
		{
			it->second.push_back(entity);
		}
	}
	else
	{
		std::vector<Entity*> vec;
		vec.push_back(entity);
		moCollidingGroups[group] = vec;
	}
}

void Stu::Engine::Scene::RemoveFromCollidingGroup(std::string group, Entity* entity)
{
	std::map<std::string, std::vector<Entity*>>::iterator it = moCollidingGroups.find(group);

	if(it != moCollidingGroups.end())
	{
		std::vector<Entity*>::iterator it2 = it->second.begin();
		for(; it2 != it->second.end(); it2++)
		{
			if(*it2 == entity)
			{
				it->second.erase(it2);
				return;
			}
		}
	}
}

void Stu::Engine::Scene::UpdateHierarchy(float deltaTime)
{
	Node::UpdateHierarchy(deltaTime);

	CalculateCollisions();
}