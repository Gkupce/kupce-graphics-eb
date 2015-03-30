#include "includes\Texture.h"

Stu::Engine::Texture::Texture(const char* name, int texCode, unsigned int height, unsigned int width)
{
	moName = name;

	miTexCode = texCode;
	muiHeight = height;
	muiWidth = width;
}

Stu::Engine::Texture::Texture(const std::string name, int texCode, unsigned int height, unsigned int width)
{
	moName = name;

	miTexCode = texCode;
	muiHeight = height;
	muiWidth = width;
}

Stu::Engine::Texture::~Texture()
{
}

unsigned int Stu::Engine::Texture::getHeight()
{
	return muiHeight;
}

unsigned int Stu::Engine::Texture::getWidth()
{
	return muiWidth;
}

std::string Stu::Engine::Texture::getName()
{
	return moName;
}

int Stu::Engine::Texture::getTexCode()
{
	return miTexCode;
}