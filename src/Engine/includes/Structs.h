#ifndef __STRUCTS_H__
#define __STRUCTS_H__

namespace Stu
{
	namespace Engine
	{
		union Color
		{
			unsigned long argb;
			struct p {
				unsigned char b,g,r,a;//a,r,g,b;
			} part;
		};

		struct ColorVertex
		{
			float x,y,z;//,rhw;
			Color color;
		};

		struct TexVertex{
			float x,y,z;
			float u,v;
		};
	}

}

#endif //__STRUCTS_H__