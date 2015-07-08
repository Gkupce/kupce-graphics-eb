#include "includes\Animation3D.h"


Stu::Engine::Animation3D::Animation3D()
{
	mfDurationTicks = 0;
	mfTicksPerSec = 1;
}

Stu::Engine::Animation3D::~Animation3D()
{
	for(auto it = moFrames.begin(); it != moFrames.end(); it++)
	{
		delete (*it);
	}
}

void Stu::Engine::Animation3D::AddFrame(Bone* frame)
{
	moFrames.push_back(frame);
	mfDurationTicks += frame->ticks;
}

void Stu::Engine::Animation3D::SetName(const char* name)
{
	moName = name;
}

std::vector<Stu::Engine::Float4x4> Stu::Engine::Animation3D::GetFrame(float time)
{
	std::vector<Float4x4> result;
	
	for(unsigned int i = 0; i < moFrames.size(); i++)
	{
		result.push_back(moFrames[i]->GetTransformation(time));
	}
	return result;
}