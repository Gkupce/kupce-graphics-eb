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
	const char* source = node.getAttribute("Source");
	if(source[0] == '.' && (source[1] == '/' || source[1] == '\\'))
		source = source + 2;

	texPath.append(source);
	if(!mpoTextureMap.count(texPath))
	{
		if(LoadTexture(texPath.c_str()))
		{//fucksies
			return true;
		}
	}

	Texture::Ptr texPtr = mpoTextureMap[texPath];

	Sprite::Ptr sprite(new Sprite(texPtr, NULL,
						atoi(node.getAttribute("X")),
						atoi(node.getAttribute("Y")),
						atoi(node.getAttribute("W")),
						atoi(node.getAttribute("H"))));
	mpoSpriteMap[node.getAttribute("Name")] = sprite;
	return false;
}

bool Stu::Engine::Importer::LoadTexture(const char* fileName)
{
	std::string path = getPath(fileName);
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Textures");

	XMLNode resNode = mainNode.getChildNode(0);//Texture node
	//std::string name = resNode.getAttribute("Name");
	unsigned int height = atoi(resNode.getAttribute("Height"));
	unsigned int width = atoi(resNode.getAttribute("Width"));
	Color col;
	
	col.part.a = atoi(resNode.getAttribute("ColorKeyA"));
	col.part.r = atoi(resNode.getAttribute("ColorKeyR"));
	col.part.g = atoi(resNode.getAttribute("ColorKeyG"));
	col.part.b = atoi(resNode.getAttribute("ColorKeyB"));

	int texCode;

	const char* source = resNode.getAttribute("Path");
	if(source[0] == '.' && (source[1] == '/' || source[1] == '\\'))
		source = source + 2;
	/*{
		texCode = mpoGame->GetRenderer()->LoadTexture(path.append(source + 2).c_str(), col);
	}
	else
	{
		texCode = mpoGame->GetRenderer()->LoadTexture(path.append(source).c_str(), col);
	}*/
	texCode = mpoGame->GetRenderer()->LoadTexture(path.append(source).c_str(), col);
	if(texCode == -1)
	{//fucksies
		return true;
	}

	Texture::Ptr texPtr(new Texture(fileName, texCode, height, width));
	mpoTextureMap[fileName] = texPtr;
	
	return false;
}

bool Stu::Engine::Importer::LoadResource(const char* fileName)
{
	XMLNode mainNode=XMLNode::openFileHelper(fileName,"Resources");

	//get the first child node
	XMLNode resNode = mainNode.getChildNode(0);
	for(int i = 1; !resNode.isEmpty(); i++)
	{//loop until we get an empty node (last node + 1)
		std::string nodeName(resNode.getName());

		if(!nodeName.compare("Sprite"))
		{//Load a Sprite
			if(LoadSprite(resNode, fileName))
			{
				return true;
			}
		}
		else if(!nodeName.compare("Animation"))
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


	return false;
}

std::string Stu::Engine::Importer::getPath(const char* fileName)
{
	std::string resul = fileName;

	int lastBar = resul.find_last_of("/\\");

	resul = resul.substr(0, lastBar+1);
	return resul;
}

Stu::Engine::Sprite Stu::Engine::Importer::GetSprite(const char* name)
{
	if(mpoSpriteMap.count(name))
	{
		return *mpoSpriteMap[name].get();
	}
	else
	{
		return NULL;
	}
}