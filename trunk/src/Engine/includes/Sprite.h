#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Entity2D.h"
#include "Texture.h"

namespace Stu
{
	namespace Engine
	{
		struct TexVertex;
		class ENGINE_API Sprite : public Entity2D
		{
		private:
			TexVertex* mptVertexs;
			Texture::Ptr mpoTexture;
		public:
			Sprite(Texture::Ptr texture, unsigned int x, unsigned int y, unsigned int width, unsigned int height);
			~Sprite();

			bool Draw(Renderer* renderer);

			SHARED_PTR(Sprite) Ptr;
		};
	}
}


#endif //__SPRITE_H__