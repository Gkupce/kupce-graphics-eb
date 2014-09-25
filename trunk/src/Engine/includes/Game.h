#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include "defines.h"

class Input;

namespace Stu
{
	namespace Engine
	{
		//Forward declarations
		class Window;
		class Renderer;
		class Timer;
		class Scene;
		class Importer;
		class Node;

		class ENGINE_API Game
		{
		public:
			Game();
			~Game();
			bool StartUp(HINSTANCE htInstance);//this method should be called at the beginning of the application. calls OnStartUp.
			bool Loop();//executes at every frame. calls OnLoop.
			bool ShutDown();//this method should be called before the object is destroyed. calls OnShutDown.
			Timer* GetTimer();
			Window* GetWindow();
			Renderer* GetRenderer();
			Importer* GetImporter();
			Input* GetInput();
		protected:
			virtual bool OnStartUp() = 0;
			virtual bool OnLoop() = 0;
			virtual bool OnShutDown() = 0;
			void SetClearColor(unsigned long clearColor);
			void SetClearColor(int a, int r, int g, int b);
			unsigned long GetClearColor();
			void AddToDrawables(Scene* entity);
			void RemoveFromDrawables(Scene* entity);
			void AddToUpdateables(Scene* entity);
			void RemoveFromUpdateables(Scene* entity);
		private:
			std::vector<Scene*> moDrawScenes;
			std::vector<Scene*> moUpdateScenes;

			Node* mpoBaseNode;
			Renderer* mpoRenderer;
			Window* mpoWindow;
			Timer* mpoTimer;
			Importer* mpoImporter;
			Input* mpoInput;
		};
	}
}

#include "Game.inl"
#endif //__GAME_H__
