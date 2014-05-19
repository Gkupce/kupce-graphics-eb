#ifndef __TIMER_H__
#define __TIMER_H__

#include "defines.h"

union _LARGE_INTEGER;
typedef _LARGE_INTEGER LARGE_INTEGER;

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
			bool mbUseQPF;

			//float lastTime;
			float deltaTime;
			//clock_t now, last;

			void FirstMeasure();
			void Measure();
		public:
			Timer();
			~Timer();
			float GetDT();
			float GetFPS();
	

			friend class Game;
		};
	}
}
#endif //__TIMER_H__