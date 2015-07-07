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
};

struct Bone
{
	int index;
	std::string name;
	std::vector<BoneFrame> frames;

	BoneFrame* GetFrame(double time)
	{
		for(auto it = frames.begin(); it != frames.end(); it++)
		{
			if(fabs(it->time - time) < 0.01f)
			{
				return it._Ptr;
			}
			else if(it->time > time)
			{//interpolate
				auto prev = it - 1;
				double ratio = (time - prev->time) / (it->time - prev->time);
				BoneFrame result;
				result.time = time;
				aiMatrix4x4 mat;
				for(int i = 0; i < 4; i++)
				{
					for(int j = 0; j < 4; j++)
					{
						mat[i][j] = prev->transform[i][j] * (1 - ratio) + prev->transform[i][j] * ratio;
					}
				}
				result.transform = mat;
				frames.insert(it, result);
				return &result;
			}
		}
		return NULL;
	}
};

struct BoneAnim
{
	std::vector<Bone> bones;
	std::string name;
	double tps;
	std::vector<float> frameTimes;
	
	BoneAnim()
	{
		frameTimes.push_back(0);//i'll assume 0 will always be there
	}

	Bone* GetBone(const char* name)
	{
		for(std::vector<Bone>::iterator it = bones.begin(); it != bones.end(); it++)
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
			Bone bone;
			bone.name = animations[i]->mChannels[j]->mNodeName.C_Str();
			if((animations[i]->mChannels[j]->mNumRotationKeys == animations[i]->mChannels[j]->mNumPositionKeys) && 
				(animations[i]->mChannels[j]->mNumPositionKeys == animations[i]->mChannels[j]->mNumScalingKeys))
			{//if the bone doesn't have the same amount of frames for rotation, translation and scaling, shit pants
				for (unsigned int k = 0; k < animations[i]->mChannels[j]->mNumPositionKeys; k++)
				{//iterate over each frame
					BoneFrame frame;
					
					frame.time = (int)animations[i]->mChannels[j]->mPositionKeys[k].mTime;
					aiMatrix4x4 aux1, aux2;
					
					aux1 = aiMatrix4x4::Translation(animations[i]->mChannels[j]->mPositionKeys[k].mValue, aux1);//translate
					aux1 = aux1 * aiMatrix4x4(animations[i]->mChannels[j]->mRotationKeys[k].mValue.GetMatrix());//rotate
					aux1 = aux1 * aiMatrix4x4::Scaling(animations[i]->mChannels[j]->mScalingKeys[k].mValue, aux2);//scale
					
					frame.transform = aux1;
					//TODO ? frame.time -= (int)animations[i]->mChannels[j]->mPositionKeys[k - 1].mTime;
					bone.frames.push_back(frame);

					bool pushed = false;
					for(auto it = anim.frameTimes.begin(); it != anim.frameTimes.end(); it++)
					{
						
						if(fabs(*it - frame.time) < 0.01f) 
						{
							pushed = true;
							break;
						}
						if(*it > frame.time)
						{
							pushed = true;
							anim.frameTimes.insert(it, frame.time);
							break;
						}
					}
					if(!pushed)
					{
						anim.frameTimes.push_back(frame.time);
					}
				}
			}
			else 
			{//poopie
				return true;
			}
			anim.bones.push_back(bone);
		}
		auxAnims.push_back(anim);
	}
	
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
			
			Bone firstBone = *it->GetBone(scene->mMeshes[j]->mBones[0]->mName.C_Str());

			for(unsigned int k = 0; k < it->frameTimes.size(); k++)
			{
				Frame3D* frame = NULL;
				frame = new Frame3D();
				if(!frame) return true;

				frame->numTransformations = scene->mMeshes[j]->mNumBones;
				if(k != 0)
				{
					frame->ticks = (float)(it->frameTimes[k] - it->frameTimes[k - 1]);
				}
				else 
				{
					frame->ticks = 0;
				}
				frame->pTransformations = new Float4x4[frame->numTransformations];
				
				if(!frame->pTransformations) 
				{
					delete frame;
					return true;
				}

				for(unsigned int i = 0; i < scene->mMeshes[j]->mNumBones; i++)
				{
					aiMatrix4x4 mat = scene->mMeshes[j]->mBones[i]->mOffsetMatrix;
					const aiNode* currentBoneNode = FindAINode(scene->mRootNode, std::string(scene->mMeshes[j]->mBones[i]->mName.C_Str()));
					
					//mat = it->GetBone(scene->mMeshes[j]->mBones[i]->mName.C_Str())->GetFrame(it->frameTimes[k])->transform * mat;
					while(currentBoneNode != NULL)
					{
						Bone* bone = it->GetBone(scene->mMeshes[j]->mBones[i]->mName.C_Str());
						if(bone)
						{
							mat = mat* bone->GetFrame(it->frameTimes[k])->transform;
						}
						currentBoneNode = currentBoneNode->mParent;
					}/**/
					mat = mat.Transpose();
					for(int l = 0; l < 4; l++)
					{
						for(int m = 0; m < 4; m++)
						{
							frame->pTransformations[i].val[l][m] = mat[l][m];
						}
					}
				}
				anim->AddFrame(frame);
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