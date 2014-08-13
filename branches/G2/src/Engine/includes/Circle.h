#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "Shape.h"

namespace Stu
{
	namespace Engine
	{
		//vertex disposition:
		//
		
		class ENGINE_API Circle : public Shape
		{
		public:
			Circle(unsigned int vertexAmount);
			bool SetFaceAmount(unsigned int faceAmount);
		};
	}
}

#endif