#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>


#include "includes\Importer.h"
#include "includes\Renderer.h"
#include "includes\Structs.h"
#include "includes\AnimatedMesh.h"
#include "includes\Skeleton.h"
#include "includes\Game.h"


#include <iostream>
//auxiliar structures
struct BoneFrame
{
	aiMatrix4x4 transform;
	double time;

	static BoneFrame GetZero()
	{
		BoneFrame result;
		for(int i = 0; i < 4; i++)
			for(int k = 0; k < 4; k++)
				result.transform[i][k] = (i == k)?1.0f:0.0f;
		result.time = 0;
		return result;
	}
};

struct AuxBone
{
	int index;
	std::string name;
	std::vector<BoneFrame> frames;

	AuxBone(aiNodeAnim* aiBone)
	{
		name = aiBone->mNodeName.C_Str();
		frames.push_back(BoneFrame::GetZero());
		for (unsigned int k = 0; k < aiBone->mNumPositionKeys; k++)
		{//iterate over each frame
			BoneFrame* frame = GetFrame(aiBone->mPositionKeys[k].mTime);
			frame->transform = frame->transform * aiMatrix4x4::Translation(aiBone->mPositionKeys[k].mValue, frame->transform);//translate
		}
		for (unsigned int k = 0; k < aiBone->mNumRotationKeys; k++)
		{
			BoneFrame* frame = GetFrame(aiBone->mPositionKeys[k].mTime);
			frame->transform = frame->transform * aiMatrix4x4(aiBone->mRotationKeys[k].mValue.GetMatrix());//rotate
		}
		for (unsigned int k = 0; k < aiBone->mNumScalingKeys; k++)
		{
			BoneFrame* frame = GetFrame(aiBone->mPositionKeys[k].mTime);
			frame->transform = frame->transform * aiMatrix4x4::Scaling(aiBone->mScalingKeys[k].mValue, frame->transform);//scale
		}
	}

	BoneFrame* GetFrame(double time)
	{
		for(auto it = frames.begin(); it != frames.end(); it++)
		{
			if(fabs(it->time - time) < 0.01f)
			{
				return it._Ptr;
			}
			else if(it->time > time)
			{
				BoneFrame frame = BoneFrame::GetZero();
				frame.time = time;
				frames.insert(it, frame);
				return GetFrame(time);
			}
		}
		BoneFrame frame = BoneFrame::GetZero();
		frame.time = time;
		frames.push_back(frame);
		return GetFrame(time);
	}
};

struct BoneAnim
{
	std::vector<AuxBone> bones;
	std::string name;
	double tps;
	
	AuxBone* GetBone(const char* name)
	{
		for(auto it = bones.begin(); it != bones.end(); it++)
		{
			if(!it->name.compare(name))
			{
				return it._Ptr;
			}
		}
		return NULL;
	}
};

//------------------------------------------------------------------------

bool Stu::Engine::Importer::LoadSceneAnimations(const aiScene* scene, std::string name)
{
	std::stringstream stringBuilder;
	aiAnimation** animations = scene->mAnimations;
	unsigned int animNum = scene->mNumAnimations;
	std::vector<BoneAnim> auxAnims;
	
	for(unsigned int i = 0; i < animNum; i++)
	{// iterate over all animations
		BoneAnim anim;
		std::string animationName = animations[i]->mName.C_Str();
		anim.tps = animations[i]->mTicksPerSecond;
		
		for (unsigned int j = 0; j < animations[i]->mNumChannels; j++)
		{//iterate over each bone
			AuxBone bone(animations[i]->mChannels[j]);
			
			anim.bones.push_back(bone);
		}
		auxAnims.push_back(anim);
	}
	//-------------------------------------------------------------------
	for(unsigned int j = 0; j < scene->mNumMeshes; j++)
	{
		if(!scene->mMeshes[j]->HasBones()) continue;

		Skeleton::Ptr skelly(new Skeleton());
		for(std::vector<BoneAnim>::iterator it = auxAnims.begin(); it != auxAnims.end(); it++)
		{
			Animation3D* anim = NULL;
			anim = new Animation3D();
			anim->SetName(it->name.c_str());
			anim->SetTicksPerSec((float)it->tps);
			
			for(unsigned int k = 0; k < scene->mMeshes[j]->mNumBones; k++)
			{
				AuxBone actualBone = *it->GetBone(scene->mMeshes[j]->mBones[k]->mName.C_Str());
				Bone* bone = NULL;
				bone = new Bone();
				if(!bone) return true;
				bone->numTransformations = actualBone.frames.size();
				bone->pFrames = new Frame3D[actualBone.frames.size()];
				if(!bone->pFrames) 
				{
					delete bone;
					return true;
				}

				for(unsigned int i = 0; i < bone->numTransformations; i++)
				{
					bone->pFrames[i].time = actualBone.frames[i].time;
					aiMatrix4x4 mat = scene->mMeshes[j]->mBones[k]->mOffsetMatrix * actualBone.frames[i].transform;

					mat = mat.Transpose();
					for(int l = 0; l < 4; l++)
					{
						for(int m = 0; m < 4; m++)
						{
							bone->pFrames[i].transformation.val[l][m] = mat[l][m];
						}
					}
				}
				anim->AddFrame(bone);
			}
			skelly->AddAnimation(anim);
		}
		stringBuilder.str(std::string());
		stringBuilder << name << "_" << j;
		moSkeletonMap[stringBuilder.str()] = skelly;//TODO PRAY
	}

	return false;
}

const aiNode* Stu::Engine::Importer::FindAINode(const aiNode* node, std::string name)
{
	if(!name.compare(node->mName.C_Str()))
	{
		return node;
	}
	else
	{
		for(unsigned int i = 0; i < node->mNumChildren; i++)
		{
			const aiNode* result = FindAINode(node->mChildren[i], name);
			if(result)
			{
				return result;
			}
		}
		return NULL;
	}
}


bool Stu::Engine::Importer::LoadAnimMesh(aiMesh* mesh, std::string meshName, std::string nodeName)
{
	if(moAnimMeshMap.count(meshName)) return true;//mesh already loaded
	std::ostringstream stringBuilder;
	stringBuilder << nodeName << "_TEX_" << (int)(mesh->mMaterialIndex);
	Texture::Ptr tex;
	if(moTextureMap.count(stringBuilder.str()) != 0)
	{
		tex = moTextureMap[stringBuilder.str()];
	}
	
	Skeleton::Ptr skl;
	skl = moSkeletonMap[meshName];

	AnimatedMesh* myMesh = NULL;
	myMesh = new AnimatedMesh(mpoGame->GetRenderer(), mesh, tex, skl);//TODO
	if(!myMesh)
	{
		return true;
	}
	stringBuilder.str(std::string());
	stringBuilder << nodeName << "_MAT_" << mesh->mMaterialIndex;
	if(moMatMap.count(stringBuilder.str()) == 0)
	{
		//return true;
		Material defMat;
		defMat.SetAmbient(1,1,1,1);
		defMat.SetDiffuse(1,1,1,1);
		defMat.SetSpecular(1,1,1,1);
		defMat.SetEmissive(0,0,0,0);
		defMat.SetSpecPow(1);
		myMesh->SetMaterial(defMat);
	}
	else
	{
		myMesh->SetMaterial(moMatMap[stringBuilder.str()]);
	}
	moAnimMeshMap[meshName] = myMesh;
	return false;
}