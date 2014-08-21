#ifndef __SCENE_H__
#define __SCENE_H__
#include "defines.h"
#include <vector>
#include <map>
#include <string>

namespace Stu
{
	namespace Engine
	{
		class Renderer;
		class Entity;

		class ENGINE_API Scene
		{
		public:
			Scene();
			~Scene();

			void AddToDrawables(Entity* entity);
			void RemoveFromDrawables(Entity* entity);
			void AddToUpdateables(Entity* entity);
			void RemoveFromUpdateables(Entity* entity);
			void AddToCollidingGroup(std::string group, Entity* entity);
			void RemoveFromCollidingGroup(std::string group, Entity* entity);
			bool IsUpdateable();
			bool IsDrawable();

			//Only called by the engine
			bool Draw(Renderer* renderer);
			void Update(float deltaTime);
			
			void SetAddedToDrawables(bool state);
			void SetUpdateable(bool state);

		protected:
			virtual void PreUpdate(float deltaTime){}//before all objects update
			virtual void PosUpdate(float deltaTime){}//after all objects update
		private:
			void CalculateCollisions();

			bool mbIsUpdateable;
			bool mbIsDrawable;

			std::vector<Entity*> moUpdateObjs;
			std::vector<Entity*> moDrawObjs;
			std::map<std::string, std::vector<Entity*>> moCollidingGroups;
		};
	}
}

#include "Scene.inl"

#endif