#ifndef __SCENE_H__
#define __SCENE_H__
#include <vector>
#include <map>
#include <string>

namespace Stu
{
	namespace Engine
	{
		class Renderer;
		class Entity2D;
		class Game;//?

		class Scene
		{
		public:
			Scene();
			~Scene();

			virtual void PreUpdate(float deltaTime){}//before all objects update
			virtual void PosUpdate(float deltaTime){}//after all objects update

			void AddToDrawables(Entity2D* entity);
			void RemoveFromDrawables(Entity2D* entity);
			void AddToUpdateables(Entity2D* entity);
			void RemoveFromUpdateables(Entity2D* entity);
			void AddToCollidingGroup(std::string group, Entity2D* entity);
			void RemoveFromCollidingGroup(std::string group, Entity2D* entity);
			
			bool Draw(Renderer* renderer);
			void Update(float deltaTime);
		private:
			void CalculateCollisions();

			std::vector<Entity2D*> moDrawUpdateObjs;
			std::map<std::string, std::vector<Entity2D*>> moCollidingGroups;
		};
	}
}

#endif