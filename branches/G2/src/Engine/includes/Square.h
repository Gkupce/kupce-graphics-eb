#ifndef __SQUARE_H__
#define __SQUARE_H__
#include "Shape.h"

namespace Stu
{
	namespace Engine
	{
		//vertex disposition:
		//1 _ 3
		// | |
		// |_|
		//0   2  
		
		class ENGINE_API Square : public Shape
		{
		public:
			Square();
		};
	}
}

#endif