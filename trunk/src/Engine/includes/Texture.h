#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "defines.h"

namespace Stu
{
	namespace Engine
	{
		class ENGINE_API Texture
		{
		private:
			char* name;
		public:
			Texture(const char* name);
			~Texture();
			
			SHARED_PTR(Texture) Ptr;
		};
	}
}

#endif //__TEXTURE_H__
