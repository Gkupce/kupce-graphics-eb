#ifndef __QUATERNION_H___
#define __QUATERNION_H___

namespace Stu
{
	namespace Engine
	{
		class Quaternion
		{
		public:
			Quaternion();
			Quaternion(float x, float y, float z, float w);
			~Quaternion();
			float x, y, z, w;
		};
	}
}

#endif