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
		class Light;

		class ENGINE_API Scene : public Node
		{
		public:
			Scene();
			~Scene();

			void AddToDrawables(Node* entity);
			void RemoveFromDrawables(Node* entity);
			void AddToUpdateables(Node* entity);
			void RemoveFromUpdateables(Node* entity);
			void AddToCollidingGroup(std::string group, Entity* entity);
			void RemoveFromCollidingGroup(std::string group, Entity* entity);
			bool IsDrawable();
			void AddLight(Light* light);//TODO
			void RemoveLight(Light* light);//TODO

			//Only called by the engine
			virtual bool DrawHierarchy(Renderer* renderer);
			//virtual void Update(float deltaTime);
			void UpdateHierarchy(float deltaTime);

			void SetAddedToDrawables(bool state, Renderer* render);
			void SwitchAllLightsState(bool enabled);
			void UpdateLights(Renderer* render);
			int FindLight(Light* light);
		private:
			void CalculateCollisions();

			Renderer* mpoRender;
			bool mbIsDrawable;

			std::vector<Node*> moUpdateObjs;
			std::vector<Entity*> moDrawObjs;
			std::vector<Light*> moLights;
			std::map<std::string, std::vector<Entity*>> moCollidingGroups;
		};
	}
}

#include "Scene.inl"

#endif