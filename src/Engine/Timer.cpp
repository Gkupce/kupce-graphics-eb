#include "includes\Timer.h"

Stu::Engine::Timer::Timer()
{
	FirstMeasure();
}

void Stu::Engine::Timer::FirstMeasure()
{
	now = clock();
}

void Stu::Engine::Timer::Measure()
{
	last = now;
	now = clock();
	deltaTime = ((double)(now - last)) / CLOCKS_PER_SEC;
}

float Stu::Engine::Timer::GetFPS()
{
	return 1 / deltaTime;
}

double Stu::Engine::Timer::GetDT()
{
	return deltaTime;
}
