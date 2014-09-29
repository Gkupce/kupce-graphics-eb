#ifndef __SCENE_H__
#define __SCENE_H__
#include "defines.h"
#include <vector>
#include <map>
#include <string>

#include "Node.h"

namespace Stu
{
	namespace Engine
	{
		class Renderer;
		class Entity;

		class ENGINE_API Scene : public Node
		{
		public:
			Scene();
			~Scene();

			void AddToDrawables(Entity* entity);
			void RemoveFromDrawables(Entity* entity);
			void AddToUpdateables(Node* entity);
			void RemoveFromUpdateables(Node* entity);
			void AddToCollidingGroup(std::string group, Entity* entity);
			void RemoveFromCollidingGroup(std::string group, Entity* entity);
			bool IsDrawable();

			//Only called by the engine
			bool Draw(Renderer* renderer);
			//virtual void Update(float deltaTime);
			void UpdateHierarchy(float deltaTime);

			void SetAddedToDrawables(bool state);
		private:
			void CalculateCollisions();

			bool mbIsDrawable;

			std::vector<Node*> moUpdateObjs;
			std::vector<Entity*> moDrawObjs;
			std::map<std::string, std::vector<Entity*>> moCollidingGroups;
		};
	}
}

#include "Scene.inl"

#endif