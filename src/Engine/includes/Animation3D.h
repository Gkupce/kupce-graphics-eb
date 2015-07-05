#ifndef __ANIMATION3D_H__
#define __ANIMATION3D_H__

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
			
			int miTicksPerSec;
			float mfTime;
			std::vector<Frame3D> moFrames;
			bool mbPlaying;
			
			float mfSpeed;
			unsigned int muiCurrentFrame;

		public:
			Animation3D();
			Animation3D(float frameTime);
			~Animation3D();

			void AddFrame(Frame3D);
			const Frame3D* getFrame(float time);
		};
	}
}

#endif //__ANIMATION3D_H__