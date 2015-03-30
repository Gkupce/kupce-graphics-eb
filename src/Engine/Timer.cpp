#include <windows.h>
#include <WinBase.h>
#include "includes\Timer.h"

Stu::Engine::Timer::Timer()
{
	mtpThisFrame = NULL;
	mtpLastFrame = NULL;
	mtpFrequency = NULL;
	FirstMeasure();
}

Stu::Engine::Timer::~Timer()
{
	if(mtpThisFrame)
	{
		delete mtpThisFrame;
		mtpThisFrame = NULL;
	}

	if(mtpLastFrame)
	{
		delete mtpLastFrame;
		mtpLastFrame = NULL;
	}

	if(mtpFrequency)
	{
		delete mtpFrequency;
		mtpFrequency = NULL;
	}
}

void Stu::Engine::Timer::FirstMeasure()
{
	mtpLastFrame = new LARGE_INTEGER;
	mtpFrequency = new LARGE_INTEGER;
	mtpThisFrame = new LARGE_INTEGER;
	if(!mtpThisFrame || !mtpLastFrame || !mtpFrequency)
	{
		throw "could not create timer (Out of memory)";
		return;
	}
	mbUseQPF = QueryPerformanceFrequency(mtpFrequency);
	if(mbUseQPF)
	{
		QueryPerformanceCounter(mtpThisFrame);
		Measure();
	}
	else
	{
		throw "could not create timer (QPF)";
	}
}

void Stu::Engine::Timer::Measure()
{
	*mtpLastFrame = *mtpThisFrame;
	QueryPerformanceCounter(mtpThisFrame);
	deltaTime = (float)((double)(mtpThisFrame->QuadPart - mtpLastFrame->QuadPart)/(double)(mtpFrequency->QuadPart));
}

float Stu::Engine::Timer::GetFPS()
{
	return 1.0f / deltaTime;
}

float Stu::Engine::Timer::GetDT()
{
	return deltaTime;
}
