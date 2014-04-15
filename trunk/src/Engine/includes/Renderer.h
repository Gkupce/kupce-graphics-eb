#ifndef __RENDERER_H__
#define __RENDERER_H__

struct IDirect3DDevice9;

namespace Stu
{
	namespace Engine
	{
		class Window;

		class Renderer
		{
		private:
			IDirect3DDevice9* mhtDevice;
			unsigned long mulClearColor; //d3dcolor is a typedef of unsigned long, so let's not add forward declarations where we know what to do
		public:
			Renderer();
			~Renderer();

			bool Init(Window* poWindow);//returns wether there was an error (true) or not (false)
			void SetClearColor(unsigned long clearColor);
			void SetClearColor(int a, int r, int g, int b);
			unsigned long GetClearColor();
			void StartFrame();
			void EndFrame();

		};
	}
}

#include "Renderer.inl"
#endif //__RENDERER_H__