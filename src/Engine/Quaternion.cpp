#include "includes\Quaternion.h"

Stu::Engine::Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Stu::Engine::Quaternion::Quaternion()
{
	x = y = z = 0;
	w = 1;
}

Stu::Engine::Quaternion::~Quaternion()
{}

