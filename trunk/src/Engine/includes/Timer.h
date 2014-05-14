#ifndef __TIMER_H__
#define __TIMER_H__

#include <time.h>
#include "defines.h"

union LARGE_INTEGER;

namespace Stu
{
	namespace Engine
	{
		class Game;

		class ENGINE_API Timer{
		private:
			/*unsigned long frequency;
			unsigned long ActualTime;*/
			LARGE_INTEGER* mtpThisFrame;
			LARGE_INTEGER* mtpLastFrame;
			LARGE_INTEGER* mtpFrequency;

			float lastTime;
			float deltaTime;
			clock_t now, last;

			void FirstMeasure();
			void Measure();
		public:
			Timer();
			float GetDT();
			float GetFPS();
	

			friend class Game;
		};
	}
}
#endif //__TIMER_H__