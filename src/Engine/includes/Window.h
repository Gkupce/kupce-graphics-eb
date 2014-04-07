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
			HINSTANCE mhInstance; // windows program instance
			HWND mhWin; //window handle
		public:
			Window(HINSTANCE hInstance);
			~Window();
			bool WindowCreate(unsigned int uiWidth, unsigned int uiHeight);
			void SetTitle(char * title);
			HWND GetWindowHandle();
		};

		#include "Window.inl"
	}
}
#endif //__WINDOW_H__