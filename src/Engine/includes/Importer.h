#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include <map>
#include <string>

#include "defines.h"
#include "Texture.h"
#include "Sprite.h"

class XMLNode;

namespace Stu
{
	namespace Engine
	{
		class Game;

		class ENGINE_API Importer
		{
		public:
			Importer(Game* game);
			~Importer();
			bool LoadResource(const char* dataPath);
			bool LoadTileMap(const char* fileName);
			Sprite* GetSprite(const char* name);
		private:
			std::map<std::string, Texture::Ptr> moTextureMap;
			std::map<std::string, Sprite*> moSpriteMap;
			Game* mpoGame;

			bool LoadAnimation(const XMLNode& node, const char* fileName);
			bool LoadTexture(const char* fileName);
			bool LoadSprite(const XMLNode& node, const char* fileName);
			
			std::string getPath(const char* fileName);
		};
	}
}

#endif //__IMPORTER_H__