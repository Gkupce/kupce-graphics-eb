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
		public:
			Renderer();
			~Renderer();

			bool Init(Window* poWindow);//returns wether there was an error (true) or not (false)
			void StartFrame();
			void EndFrame();

		};
	}
}

#endif //__RENDERER_H__