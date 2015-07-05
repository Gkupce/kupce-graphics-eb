#include <iostream>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "includes\XMLParser.h"

#include "includes\Importer.h"
#include "includes\Renderer.h"
#include "includes\Structs.h"
#include "includes\Mesh.h"
#include "includes\Skeleton.h"

bool Stu::Engine::Importer::LoadSceneAnimations(const aiScene* scene)
{
	aiAnimation** animations = scene->mAnimations;
	unsigned int animNum = scene->mNumAnimations;
	//scene->mMeshes[mNumMeshes]->mBones[mNumBones]
	
	for(unsigned int i = 0; i < animNum; i++)
	{// iterate over all animations
		std::string animationName = animations[i]->mName.C_Str();
		double tps = animations[i]->mTicksPerSecond;
		for (unsigned int j = 0; j < animations[i]->mNumChannels; j++)
		{
			std::string boneName = animations[i]->mChannels[j]->mNodeName.C_Str();
			std::cout << boneName << " anim\n numPos: " << animations[i]->mChannels[j]->mNumPositionKeys;
			std::cout << "\n numRot: " << animations[i]->mChannels[j]->mNumRotationKeys;
			std::cout << "\n numScale: " << animations[i]->mChannels[j]->mNumScalingKeys << std::endl;
			std::cout << "times: ";
			for (unsigned int k = 0; k < animations[i]->mChannels[j]->mNumPositionKeys; k++)
			{
				int tick = (int)animations[i]->mChannels[j]->mPositionKeys[k].mTime;
				//animations[i]->mChannels[j]->
			}
			std::cout << std::endl;
		}

		std::cout << "--------------------------------------------------------------" << std::endl;
	}

	return false;
}