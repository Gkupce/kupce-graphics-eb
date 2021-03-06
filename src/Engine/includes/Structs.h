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

		struct TexNormalVertex{
			float x,y,z;
			float nX,nY,nZ;
			float u,v;
		};


		//------------------------------------------------------------
		//3D animations
		/**4 by 4 float Matrix for transformations*/
		struct Float4x4 {
			float val[4][4];
		};
		struct Frame3D
		{
			Frame3D ()
			{
				pTransformations = NULL;
			}
			~Frame3D()
			{
				if(pTransformations)
				{
					delete[] pTransformations;
					pTransformations = NULL;
				}
			}

			Frame3D Copy()
			{
				Frame3D copy;
				copy.numTransformations = this->numTransformations;
				copy.ticks = this->ticks;
				copy.pTransformations = new Float4x4[copy.numTransformations];
				if(!copy.pTransformations) throw "out of memory";

				for(unsigned int i = 0; i < copy.numTransformations; i++)
				{
					memcpy(copy.pTransformations[i].val, this->pTransformations[i].val, sizeof(float) * 4 * 4);
				}
				return copy;
			}

			float ticks;

			Float4x4* pTransformations;
			unsigned int numTransformations;
		};

		//TODO ---------------------------------------------------------------------------
		struct TexNormalAnimVertex{
			float x,y,z;
			float nX,nY,nZ;
			float u,v;
			float weight[4];
			BYTE bIndx[4];
		};

		const BYTE InvalidBoneIndex = 255;

		struct Frame
		{
			Frame ()
			{
				x = y = w = h = 0;
			}
			Frame (unsigned int px, unsigned int py, unsigned int pw, unsigned int ph)
			{
				x = px;
				y = py;
				w = pw;
				h = ph;
			}
			unsigned int x,y,w,h;
		};

		enum LightType
		{
			Point        = 0,
			Spot         = 1,
			Directional  = 2
		};
	}

}

#endif //__STRUCTS_H__