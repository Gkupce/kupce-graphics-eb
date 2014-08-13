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
		protected:
			ColorVertex * mptVertexs;
			unsigned int muiVertexCount;
			int miDrawPrimitive;
		public:
			Shape();
			~Shape();

			virtual bool Draw(Renderer* renderer);
			void SetColor(unsigned long color);
			void SetColor(char a, char r, char g, char b);
			void SetColor(int vertex, unsigned long color);
			void SetColor(int vertex, char a, char r, char g, char b);
			unsigned long GetColor(int vertex); //0xaarrggbb
			void GetColor(char* a, char* r, char* g, char* b, int vertex);
		};
	}
}

#endif //__SHAPE_H__