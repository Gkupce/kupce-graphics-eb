#include <map>
#include <string>

#include "includes\XMLParser.h"

#include "includes\Importer.h"
#include "includes\Renderer.h"

Stu::Engine::Importer::Importer()
{
	mpoTextureMap = NULL;

	mpoTextureMap = new std::map<std::string, Texture::Ptr>();
	if(!mpoTextureMap)
	{
		throw "Texture importer could not be initialized";
	}
}

Stu::Engine::Importer::~Importer()
{
	if(mpoTextureMap)
	{
		delete mpoTextureMap;
		mpoTextureMap = NULL;
	}
}

bool Stu::Engine::Importer::LoadSprite(const char* path)
{
	return true;
}

bool Stu::Engine::Importer::LoadTexture(const char* path)
{
	XMLNode mainNode=XMLNode::openFileHelper(path,"Textures");

	XMLNode resNode = mainNode.getChildNode(0);//Texture node
	for(int i = 1; !resNode.isEmpty(); i++)
	{//loop until we get an empty node (last node + 1)

	}

	return true;
}

bool Stu::Engine::Importer::LoadResource(const char* dataPath)
{
	XMLNode mainNode=XMLNode::openFileHelper(dataPath,"Resources");

	//get the first child node
	XMLNode resNode = mainNode.getChildNode(0);
	for(int i = 1; !resNode.isEmpty(); i++)
	{//loop until we get an empty node (last node + 1)
		std::string nodeName(resNode.getName());

		if(nodeName.compare("Sprite"))
		{//Load a Sprite

		}
		else if(nodeName.compare("Animation"))
		{//Load an animation

		}
		/*
		else if(nodeName.compare("Sound"))
		{//Load a sound
			//if i ever get to it
		}
		*/
		resNode = mainNode.getChildNode(i);
	}


	return true;
}