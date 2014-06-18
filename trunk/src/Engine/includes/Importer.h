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
		private:
			std::map<std::string, Texture::Ptr> mpoTextureMap;
			std::map<std::string, Sprite::Ptr> mpoSpriteMap;
			Game* mpoGame;

			bool LoadTexture(const char* fileName);
			bool LoadSprite(const XMLNode& node, const char* fileName);
			std::string getPath(const char* fileName);

		public:
			Importer(Game* game);
			~Importer();
			bool LoadResource(const char* dataPath);
			Sprite* GetSprite(const char* name);
		};
	}
}

#endif //__IMPORTER_H__