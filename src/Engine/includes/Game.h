#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"

namespace Stu
{
	namespace Engine
	{
		//Forward declarations
		class Window;
		class Renderer;

		class ENGINE_API Game
		{
		private:
			Renderer* mpoRenderer;
			Window* mpoWindow;
		public:
			Game();
			~Game();
			bool StartUp(HINSTANCE htInstance);//this method should be called at the beginning of the application. calls OnStartUp.
			bool Loop();//executes at every frame. calls OnLoop.
			bool ShutDown();//this method should be called before the object is destroyed. calls OnShutDown.
		protected:
			virtual bool OnStartUp() = 0;
			virtual bool OnLoop() = 0;
			virtual bool OnShutDown() = 0;
		};
	}
}
#endif //__GAME_H__
