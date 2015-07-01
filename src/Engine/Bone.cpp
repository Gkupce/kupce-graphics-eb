#include "includes\Bone.h"
#include "includes\Structs.h"

Stu::Engine::Bone::Bone()
{
	mptTransformations = NULL;
	mptWeights = NULL;
}

Stu::Engine::Bone::~Bone()
{
	if(mptTransformations)
	{
		delete[] mptTransformations;
		mptTransformations = NULL;
	}
	if(mptWeights)
	{
		delete[] mptWeights;
		mptWeights = NULL;
	}
}

float Stu::Engine::Bone::GetWeight(unsigned int vertex)
{
	for(unsigned int i = 0; i < muiWeightsAmount; i++)
	{
		if(mptWeights[i].first == vertex)
		{
			return mptWeights[i].second;
		}
	}
}