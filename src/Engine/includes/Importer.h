#ifndef __IMPORTER_H__
#define __IMPORTER_H__

#include <map>
#include <string>

#include "defines.h"
#include "Texture.h"
#include "Sprite.h"
#include "Material.h"

struct XMLNode;
struct aiMesh;
struct aiScene;
struct aiNode;

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

			Node* GetMesh(const char* name);

		private:
			std::map<std::string, Texture::Ptr> moTextureMap;
			std::map<std::string, Sprite*> moSpriteMap;
			std::map<std::string, Tilemap*> moTilemapMap;
			std::map<std::string, Node*> moNodeMap;
			std::map<std::string, Mesh*> moMeshMap;
			std::map<std::string, Material> moMatMap;

			Game* mpoGame;

			bool LoadSceneAnimations(const aiScene* scene);
			bool LoadAnimation(const XMLNode& node, const char* fileName);
			bool LoadTexture(const char* fileName);
			bool LoadSprite(const XMLNode& node, const char* fileName);
			bool LoadScene(const XMLNode& node, const char* fileName);
			bool CreateTexture(const char* path, const char* name, Color colorKey, int height, int width);
			bool CreateTexture(const char* path, const char* name, Color colorKey);
			bool LoadMesh(aiMesh* mesh, std::string name, std::string nodeName);
			bool LoadSceneTextures(const aiScene* scene, std::string name, const char* fileName);
			Node* LoadNodeStructure(const aiNode* node, std::string name, const char* bspBaseName);

			std::string getPath(const char* fileName);
		};
	}
}

#endif //__IMPORTER_H__