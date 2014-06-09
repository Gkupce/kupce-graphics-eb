#ifndef __IMPORTER_H__
#define __IMPORTER_H__
#include "defines.h"
#include "Texture.h"

namespace std
{
	template <class Key, class T, class Compare = less<Key>,
				class Alloc = allocator<pair<const Key,T>> >
	class map;
	//template <class c>
	//class base_string;
	typedef string;
}

namespace Stu
{
	namespace Engine
	{
		class Sprite;

		class ENGINE_API Importer
		{
		private:
			std::map<std::string, Texture::Ptr>* mpoTextureMap;
			std::map<std::string, Sprite*>* mpoSpriteMap;
			bool LoadTexture(const char* path);
			bool LoadSprite(const char* dataPath);
		public:
			Importer();
			~Importer();
			bool LoadResource(const char* dataPath);
			Sprite GetSprite(const char* name);
		};
	}
}

#endif //__IMPORTER_H__