#include "includes\Scene.h"
#include "includes\Entity2D.h"

Stu::Engine::Scene::Scene()
{

}

Stu::Engine::Scene::~Scene()
{

}


bool Stu::Engine::Scene::Draw(Renderer* renderer)
{
	for(unsigned int i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if((moDrawUpdateObjs.at(i))->IsAddedToDrawables())
			if((moDrawUpdateObjs.at(i))->Draw(renderer)) return true;
	}

	return false;
}

void Stu::Engine::Scene::Update(float dt)
{
	PreUpdate(dt);

	for(unsigned int i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if((moDrawUpdateObjs.at(i))->IsUpdateable())
				(moDrawUpdateObjs.at(i))->Update(dt);
	}

	CalculateCollisions();

	PosUpdate(dt);
}


void Stu::Engine::Scene::AddToDrawables(Entity2D* entity)
{
	if(!entity->IsUpdateable())//it's not already there
		moDrawUpdateObjs.push_back(entity);
	entity->SetAddedToDrawables(true);
}

void Stu::Engine::Scene::RemoveFromDrawables(Entity2D* entity)
{
	unsigned int i;

	if(!entity->IsAddedToDrawables()) return;//is not added to drawables, don't even check
	if(entity->IsUpdateable())
	{//it should stay
		entity->SetAddedToDrawables(false);
		return;
	}

	for(i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if(moDrawUpdateObjs.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moDrawUpdateObjs.size()) return;

	moDrawUpdateObjs.erase(moDrawUpdateObjs.begin() + i);

	entity->SetAddedToDrawables(false);
}

void Stu::Engine::Scene::AddToUpdateables(Entity2D* entity)
{
	if(!entity->IsAddedToDrawables())//it's not already there
		moDrawUpdateObjs.push_back(entity);
	entity->SetUpdateable(true);
}

void Stu::Engine::Scene::RemoveFromUpdateables(Entity2D* entity)
{
	unsigned int i;

	if(!entity->IsUpdateable()) return;//is not added to drawables, don't even check
	if(entity->IsAddedToDrawables())
	{//it should stay
		entity->SetUpdateable(false);
		return;
	}

	for(i = 0; i < moDrawUpdateObjs.size(); i++)
	{
		if(moDrawUpdateObjs.at(i) == entity)
		{
			break;
		}
	}
	
	if(i == moDrawUpdateObjs.size()) return;

	moDrawUpdateObjs.erase(moDrawUpdateObjs.begin() + i);

	entity->SetUpdateable(false);
}

void Stu::Engine::Scene::CalculateCollisions()
{
	for(std::map<std::string, std::vector<Entity2D*>>::iterator it = moCollidingGroups.begin(); 
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
