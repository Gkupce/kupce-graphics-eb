#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "Shape.h"

namespace Stu
{
	namespace Engine
	{
		//vertex disposition:
		//1
		// |\
		// L_>
		//0   2  

		class ENGINE_API Triangle : public Shape
		{
		public:
			Triangle();
		};
	}
}

#endif