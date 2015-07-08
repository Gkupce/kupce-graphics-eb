#ifndef __ANIMATION3D_H__
#define __ANIMATION3D_H__

#include <string>
#include <vector>

#include "defines.h"
#include "Structs.h"

namespace Stu
{
	namespace Engine
	{
		class ENGINE_API Animation3D
		{
		private:
			
			float mfTicksPerSec;
			float mfDurationTicks;
			std::vector<Bone*> moFrames;
			std::string moName;

		public:
			Animation3D();
			~Animation3D();

			void SetTicksPerSec(float tps) { if(tps != 0) mfTicksPerSec = tps;}
			void SetName(const char*);
			void AddFrame(Bone* frame);
			std::vector<Float4x4> GetFrame(float time);
			const std::string GetName() const { return moName; }
		};
	}
}

#endif //__ANIMATION3D_H__