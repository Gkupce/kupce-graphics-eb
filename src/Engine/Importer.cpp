#include "includes\XMLParser.h"

#include "includes\Importer.h"
#include "includes\Renderer.h"
#include "includes\Texture.h"
#include "includes\Game.h"
#include "includes\Structs.h"

Stu::Engine::Importer::Importer(Game* game)
{
	mpoGame = game;
}

Stu::Engine::Importer::~Importer()
{
	for(std::map<std::string, Texture::Ptr>::iterator it = mpoTextureMap.begin(); 
		it != mpoTextureMap.end(); it++)
	{
		it->second.reset();
	}
	
}

bool Stu::Engine::Importer::LoadSprite(const XMLNode& node, const char* fileName)
{
	//<Sprite Name="name" Source="sourcePath.xml" X="x" Y="y" H="h" W="w"/>
	std::string texPath = getPath(fileName);

	texPath.append(node.getAttribute("Source"));
	if(!mpoTextureMap.count(texPath))
	{
		if(!LoadTexture(texPath.c_str()))
		{//fucksies
			return false;
		}
	}

	Texture::Ptr texPtr = mpoTextureMap[texPath];

	Sprite::Ptr sprite(new Sprite(texPtr,
						atoi(node.getAttribute("X")),
						atoi(node.getAttribute("Y")),
						atoi(node.getAttribute("W")),
						atoi(node.getAttribute("H"))));

	return true;
}

bool Stu::Engine::Importer::LoadTexture(const char* fileName)
{
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Textures");

	XMLNode resNode = mainNode.getChildNode(0);//Texture node
	//std::string name = resNode.getAttribute("Name");
	unsigned int height = atoi(resNode.getAttribute("Height"));
	unsigned int width = atoi(resNode.getAttribute("Width"));
	Color col;
	col.argb = atol(resNode.getAttribute("ColorKey"));
	int texCode = mpoGame->GetRenderer()->LoadTexture(resNode.getAttribute("Path"), col);
	
	if(texCode == -1)
	{//fucksies
		return false;
	}

	Texture::Ptr texPtr(new Texture(fileName, texCode, height, width));
	mpoTextureMap[fileName] = texPtr;
	
	return true;
}

bool Stu::Engine::Importer::LoadResource(const char* fileName)
{
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Resources");

	//get the first child node
	XMLNode resNode = mainNode.getChildNode(0);
	for(int i = 1; !resNode.isEmpty(); i++)
	{//loop until we get an empty node (last node + 1)
		std::string nodeName(resNode.getName());

		if(nodeName.compare("Sprite"))
		{//Load a Sprite
			LoadSprite(resNode, fileName);
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

std::string Stu::Engine::Importer::getPath(const char* fileName)
{
	std::string resul = fileName;

	int lastBar = resul.find_last_of('\\');

	return resul.substr(0, lastBar);
}