#ifndef __SKELETON_H__
#define __SKELETON_H__
#include <string>
#include <vector>

#include "defines.h"
#include "Structs.h"
#include "Animation3D.h"

namespace Stu
{
	namespace Engine
	{
		
		class Skeleton
		{
		public:
			SHARED_PTR(Skeleton) Ptr;
			
			Skeleton();
			~Skeleton();

			void AddAnimation(Animation3D*);

			int GetAnimationIndex(const char* animation) const;

			Frame3D GetInterpolatedFrame(unsigned int animation, float time) const;
			Frame3D GetInterpolatedFrame(std::string animation, float time) const;
		private:
			std::vector<Animation3D*> moAnimations;
			
			//Frame3D* mpoFrames;//array of bones for easy access
		};
	}
}

#endif //__SKELETON_H__