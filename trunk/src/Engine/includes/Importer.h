#ifndef __IMPORTER_H__
#define __IMPORTER_H__
#include "defines.h"
#include "Texture.h"

namespace std
{
	template <class Key, class T, class Compare = less<Key>,
				class Alloc = allocator<pair<const Key,T>> > 
	class map;
	template <class c>
	class base_string;
	typedef string<char>;
}

namespace Stu
{
	namespace Engine
	{
		class ENGINE_API Importer
		{
		private:
			std::map<std::string, Texture::Ptr>* mpoTextureMap;
			bool LoadTexture(const char* path);

		public:
			Importer();
			~Importer();
			bool LoadSprite(const char* dataPath);
		};
	}
}

#endif //__IMPORTER_H__