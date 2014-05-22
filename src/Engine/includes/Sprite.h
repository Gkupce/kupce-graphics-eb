#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Entity2D.h"

namespace Stu
{
	namespace Engine
	{
		struct TexVertex;
		class ENGINE_API Sprite : public Entity2D
		{
		private:
			TexVertex* mptVertexs;
			//Texture* texture;//wtf am i doing?
		public:
			Sprite();
			~Sprite();

			bool Draw(Renderer* renderer);

		};
	}
}


#endif //__SPRITE_H__