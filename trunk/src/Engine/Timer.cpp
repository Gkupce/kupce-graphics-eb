#include <WinBase.h>
#include "includes\Timer.h"

Stu::Engine::Timer::Timer()
{
	FirstMeasure();
}

void Stu::Engine::Timer::FirstMeasure()
{
	now = clock();
	bool use_qpf = false;
	LARGE_INTEGER* now = NULL;
	
	now = new LARGE_INTEGER;
	if(!now) 
	{
		throw "can't create timer";
		return;
	}
	use_qpf = QueryPerformanceFrequency(now);
	if(use_qpf)
	{

	}
	else
	{

	}
}

void Stu::Engine::Timer::Measure()
{
	last = now;
	now = clock();
	deltaTime = ((float)(now - last)) / CLOCKS_PER_SEC;
}

float Stu::Engine::Timer::GetFPS()
{
	return 1.0f / deltaTime;
}

float Stu::Engine::Timer::GetDT()
{
	return deltaTime;
}
