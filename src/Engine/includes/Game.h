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
		class Entity2D;
		class Importer;

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
			void AddToDrawables(Entity2D* entity);
			void RemoveFromDrawables(Entity2D* entity);
			void AddToUpdateables(Entity2D* entity);
			void RemoveFromUpdateables(Entity2D* entity);
		private:
			std::vector<Entity2D*> moDrawUpdateObjs;
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
