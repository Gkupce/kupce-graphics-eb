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
			Float4x4 transformation;
			float time;
		};

		struct Bone
		{
			Bone ()
			{
				pFrames = NULL;
			}
			~Bone()
			{
				if(pFrames)
				{
					delete[] pFrames;
					pFrames = NULL;
				}
			}

			Bone Copy()
			{
				Bone copy;
				copy.numTransformations = this->numTransformations;
				copy.ticks = this->ticks;
				copy.pFrames = new Frame3D[copy.numTransformations];
				if(!copy.pFrames) throw "out of memory";

				for(unsigned int i = 0; i < copy.numTransformations; i++)
				{
					memcpy(&copy.pFrames[i], &this->pFrames[i], sizeof(Frame3D));
				}
				return copy;
			}

			Float4x4 GetTransformation(float time)
			{
				float altTime = time;
				int frameIndex = 0;
				while(altTime > 0)
				{
					frameIndex++;
					if(frameIndex == numTransformations)
					{
						frameIndex = 0;
					}
					altTime -= pFrames[frameIndex].time;
				}
				int frameIndexL = frameIndex - 1;
				if(frameIndexL < 0)
				{
					frameIndexL = numTransformations - 1;
				}
				altTime += pFrames[frameIndex].time;

				Float4x4 result;
				float ratio = altTime / pFrames[frameIndex].time;
				for(int i = 0; i < 4; i++)
				{
					for(int k = 0; k < 4; k++)
					{
						result.val[i][k] = pFrames[frameIndexL].transformation.val[i][k] * (1 - ratio) + 
										pFrames[frameIndex].transformation.val[i][k] * ratio;
					}
				}
				return result;
			}

			float ticks;

			Frame3D* pFrames;
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