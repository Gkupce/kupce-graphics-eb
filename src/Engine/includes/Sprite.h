#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "Entity2D.h"
#include "Texture.h"
#include "Structs.h"

namespace Stu
{
	namespace Engine
	{
		class Animation2D;

		class ENGINE_API Sprite : public Entity2D
		{
		private:
			TexVertex* mptVertexs;
			Texture::Ptr mpoTexture;
			Frame msCurrentFrame;
			Animation2D* mpoAnimator;
		public:
			Sprite(Texture::Ptr texture, Animation2D* animator,
										unsigned int x, unsigned int y, 
										unsigned int width, unsigned int height);
			Sprite();

			void SetVertexs();
			void Clone(const Sprite* copyFrom);
			void SetFrame(Frame frame);

			~Sprite();

			bool Draw(Renderer* renderer);
			virtual void Update(Game* game);
		};
	}
}


#endif //__SPRITE_H__