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
			char* mpcName;
			int miTexCode;//Texture handle
			unsigned int muiHeight, muiWidth;//Texture size in pixels
			
		public:
			
			Texture(const char* name, int texPtr, unsigned int height, unsigned int width);
			~Texture();
			
			unsigned int getHeight();
			unsigned int getWidth();

			char* getName();
			int getTexCode();

			SHARED_PTR(Texture) Ptr;
		};
	}
}

#endif //__TEXTURE_H__