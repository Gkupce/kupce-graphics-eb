#ifndef __UTILS_H__
#define __UTILS_H__

struct quat_t
{
	float w,x,y,z;
};

namespace Stu
{
	namespace Engine
	{
		class Vector3;
	}
}

Stu::Engine::Vector3 QuatToEuler(const quat_t quat);

#endif