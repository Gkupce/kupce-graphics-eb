#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <Windows.h>

#include "defines.h"

namespace Stu
{
	namespace Engine
	{

		class ENGINE_API Window
		{
		private:
			HINSTANCE mhtInstance; // windows program instance
			HWND mhtWin; //window handle
		public:
			Window(HINSTANCE hInstance);
			~Window();
			bool WindowCreate(unsigned int uiWidth, unsigned int uiHeight);
			void SetTitle(char * ctitle);
			HWND GetWindowHandle();
		};

		#include "Window.inl"
	}
}
#endif //__WINDOW_H__