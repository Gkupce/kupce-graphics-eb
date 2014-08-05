#ifndef __TILE_H__
#define __TILE_H__

#include "Sprite.h"

namespace Stu
{
	namespace Engine
	{
		class Tilemap;
		class ENGINE_API Tile : public Sprite
		{
		public:
			Tile(Texture::Ptr texture, Animation2D* animator,
										unsigned int x, unsigned int y, 
										unsigned int width, unsigned int height);
			Tile();
			~Tile();

			void Clone(const Tile* copyFrom);
			virtual bool Draw(Renderer* renderer);
			void SetParent(Tilemap* parent);
		private:
			Tilemap* mpoParent;
		};
	}
}

#endif //__TILE_H__