#include <string.h>
#include "includes\Texture.h"

Stu::Engine::Texture::Texture(const char* name, void* texPtr, unsigned int height, unsigned int width)
{
	mpcName = NULL;
	mpcName = new char[strlen(name) + 1];
	if(!mpcName)
	{
		throw "Out of memory loading texture";
	}

	strcpy(mpcName, name);

	mhtTexPtr = texPtr;
	muiHeight = height;
	muiWidth = width;
}

Stu::Engine::Texture::~Texture()
{
	if(mpcName)
	{
		delete[] mpcName;
		mpcName = NULL;
	}
}

unsigned int Stu::Engine::Texture::getHeight()
{
	return muiHeight;
}

unsigned int Stu::Engine::Texture::getWidth()
{
	return muiWidth;
}

char* Stu::Engine::Texture::getName()
{
	return mpcName;
}

void* Stu::Engine::Texture::getTexPtr()
{
	return mhtTexPtr;
}