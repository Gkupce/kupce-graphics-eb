#ifndef __SKELETON_H__
#define __SKELETON_H__
#include "defines.h"

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
			Bone** mpoBonesArray;//array of bones for easy access
			//int miBaseBoneIndex;//base bone index for tree structure
		};
	}
}

#endif //__SKELETON_H__