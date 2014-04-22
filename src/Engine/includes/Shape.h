#ifndef __SHAPE_H__
#define __SHAPE_H__
#include "Entity2D.h"

namespace Stu
{
	namespace Engine
	{
		struct ColorVertex;

		class ENGINE_API Shape : public Entity2D
		{
		private:
			ColorVertex * mptVertexs;
			unsigned int muiVertexCount;
		public:
			Shape();
			~Shape();

			virtual bool Draw(Renderer* renderer);
		};
	}
}

#endif //__SHAPE_H__