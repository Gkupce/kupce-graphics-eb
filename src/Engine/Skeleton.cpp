#include "includes\Skeleton.h"


Stu::Engine::Skeleton::Skeleton()
{

}

Stu::Engine::Skeleton::~Skeleton()
{
	for(std::vector<Animation3D*>::iterator it = moAnimations.begin(); 
		it != moAnimations.end(); it++)
	{
		delete (*it);
	}
}

Stu::Engine::Frame3D Stu::Engine::Skeleton::GetInterpolatedFrame(std::string animation, float time) const
{
	int index = GetAnimationIndex(animation.c_str());
	if(index == -1) return Frame3D();
	
	return GetInterpolatedFrame((unsigned int)index, time);
}

void Stu::Engine::Skeleton::AddAnimation(Animation3D* anim)
{
	moAnimations.push_back(anim);
}

Stu::Engine::Frame3D Stu::Engine::Skeleton::GetInterpolatedFrame(unsigned int animation, float time) const
{
	if (animation >= moAnimations.size()) return Frame3D();
	
	return moAnimations[animation]->GetFrame(time);
}

int Stu::Engine::Skeleton::GetAnimationIndex(const char* name) const
{
	for(unsigned int i = 0; i < moAnimations.size(); i++)
	{
		if(!moAnimations[i]->GetName().compare(name))
		{
			return i;
		}
	}
	return -1;
}