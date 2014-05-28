#include <map>
#include <string>

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
	return true;
}