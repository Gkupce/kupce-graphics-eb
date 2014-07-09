#ifndef __AABB2D_H__
#define __AABB2D_H__

#include "defines.h"

namespace Stu
{
	namespace Engine
	{
		class Entity2D;

		class AABB2D
		{
		public:
			AABB2D(Entity2D* container);
			~AABB2D();

			bool CollidesWith(AABB2D* other);
		private:
			Entity2D* mpoContainer;

		};
	}
}

#endif //__AABB2D_H__