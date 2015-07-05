#ifndef __SKELETON_H__
#define __SKELETON_H__
#include <string>
#include <map>

#include "defines.h"
#include "Structs.h"

namespace Stu
{
	namespace Engine
	{
		//Forward declarations
		class Bone;

		class ENGINE_API Skeleton
		{
		public:
			SHARED_PTR(Skeleton) Ptr;
			
			Skeleton();
			~Skeleton();
		private:
			std::map<std::string, Frame3D*> moAnimations;
			
			//Frame3D* mpoFrames;//array of bones for easy access
		};
	}
}

#endif //__SKELETON_H__