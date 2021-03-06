#ifndef __TILEMAP_H__
#define __TILEMAP_H__
#include "Entity.h"


namespace Stu
{
	namespace Engine
	{
		class Tile;
		class Renderer;

		class ENGINE_API Tilemap : public Entity
		{
		public:
			Tilemap(int width, int height, int layerCount);
			Tilemap();
			~Tilemap();

			bool Clone(const Tilemap* other);


			
			virtual bool Draw(Renderer* renderer);
			void SetTile(int x, int y, int layer, Tile* tile);
		private:
			Tile** mpoTiles;
			int miWidth, miHeight, miLayerCount;
		};
	}
}

#endif //__TILEMAP_H__