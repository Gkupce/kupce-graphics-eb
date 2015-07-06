#include "includes\Animation3D.h"


Stu::Engine::Animation3D::Animation3D()
{
	mfDurationTicks = 0;
	mfTicksPerSec = 1;
}

Stu::Engine::Animation3D::~Animation3D()
{

}

void Stu::Engine::Animation3D::AddFrame(Frame3D frame)
{
	moFrames.push_back(frame.Copy());
	mfDurationTicks += frame.ticks;
}

void Stu::Engine::Animation3D::SetName(const char* name)
{
	moName = name;
}

const Stu::Engine::Frame3D Stu::Engine::Animation3D::GetFrame(float time)
{
	float ticks = time * mfTicksPerSec;
	while(ticks > mfDurationTicks) ticks -=mfDurationTicks;

	int posFrame = 0;
	while (ticks > 0)
	{
		ticks -= moFrames[posFrame].ticks;
		posFrame++;
		if(posFrame == moFrames.size())
			posFrame = 0;
	}
	Frame3D* nextFrame, *lastFrame;
	nextFrame = &moFrames[posFrame];
	if(posFrame == 0)
	{
		lastFrame = &moFrames[moFrames.size() - 1];
	}
	else
	{
		lastFrame = &moFrames[posFrame - 1];
	}
	float timeRatio = (ticks + lastFrame->ticks) / lastFrame->ticks;

	Frame3D result;
	result.numTransformations = moFrames[posFrame].numTransformations;
	result.pTransformations = new Float4x4[moFrames[posFrame].numTransformations];
	if(!result.pTransformations) throw "out of memory";
	
	for(int i = 0; i < result.numTransformations; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			for(int k = 0; k < 4; k++)
			{
				result.pTransformations[i].val[j][k] = 
						lastFrame->pTransformations[i].val[j][k] * (1-timeRatio) + 
						nextFrame->pTransformations[i].val[j][k] + timeRatio;//TODO lerp
			}
		}
	}
	return result;
}