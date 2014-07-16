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
		class Entity2D;

		class ENGINE_API Scene
		{
		public:
			Scene();
			~Scene();

			void AddToDrawables(Entity2D* entity);
			void RemoveFromDrawables(Entity2D* entity);
			void AddToUpdateables(Entity2D* entity);
			void RemoveFromUpdateables(Entity2D* entity);
			void AddToCollidingGroup(std::string group, Entity2D* entity);
			void RemoveFromCollidingGroup(std::string group, Entity2D* entity);
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

			std::vector<Entity2D*> moUpdateObjs;
			std::vector<Entity2D*> moDrawObjs;
			std::map<std::string, std::vector<Entity2D*>> moCollidingGroups;
		};
	}
}

#include "Scene.inl"

#endif