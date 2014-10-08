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
		class Tilemap;
		class Mesh;

		class ENGINE_API Importer
		{
		public:
			Importer(Game* game);
			~Importer();
			bool LoadResource(const char* dataPath);
			bool LoadTileMap(const char* dataPath);
			const Sprite* GetSprite(const char* name);
			const Tilemap* GetTileMap(const char* name);

			Mesh* GetMesh();

		private:
			std::map<std::string, Texture::Ptr> moTextureMap;
			std::map<std::string, Sprite*> moSpriteMap;
			std::map<std::string, Tilemap*> moTilemapMap;
			std::map<std::string, Mesh*> moMeshMap;

			Game* mpoGame;

			bool LoadAnimation(const XMLNode& node, const char* fileName);
			bool LoadTexture(const char* fileName);
			bool LoadSprite(const XMLNode& node, const char* fileName);
			bool LoadMesh(const XMLNode& node, const char* fileName);
			bool CreateTexture(const char* path, const char* name, Color colorKey, int height, int width);
			
			std::string getPath(const char* fileName);
		};
	}
}

#endif //__IMPORTER_H__