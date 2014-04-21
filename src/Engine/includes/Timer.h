#ifndef __TIMER_H__
#define __TIMER_H__

#include <time.h>
#include "defines.h"

namespace Stu
{
	namespace Engine
	{
		class Game;

		class ENGINE_API Timer{
		private:
			/*unsigned long frequency;
			unsigned long ActualTime;*/
			double lastTime;
			double deltaTime;
			clock_t now, last;

			void FirstMeasure();
			void Measure();
		public:
			Timer();
			double GetDT();
			float GetFPS();
	

			friend class Game;
		};
	}
}
#endif //__TIMER_H__