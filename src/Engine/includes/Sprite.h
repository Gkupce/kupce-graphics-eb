#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Entity2D.h"

namespace Stu
{
	namespace Engine
	{
		struct TexVertex;
		class Texture;
		class ENGINE_API Sprite : public Entity2D
		{
		private:
			TexVertex* mptVertexs;
			Texture* mpoTexture;
		public:
			Sprite(Texture* texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
			~Sprite();

			bool Draw(Renderer* renderer);

		};
	}
}


#endif //__SPRITE_H__