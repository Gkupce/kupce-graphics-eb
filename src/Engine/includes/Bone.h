#ifndef __BONE_H__
#define __BONE_H__

#include <utility>

#include "defines.h"

struct aiBone;

namespace Stu
{
	namespace Engine
	{
		/**
			Helper matrix
		*/
		struct Float4x4;

		class ENGINE_API Bone //?
		{
		public:
			//SHARED_PTR(Bone) Ptr;
			Bone();
			~Bone();//The bones should be deleted by the skeleton

			//transformMatrix getTransformation(ticks);
			float GetWeight(unsigned int vertex);
		private:
			//Bone** mpoChilds;
			/**Matrix vector containing each keyrame position*/
			Float4x4* mptTransformations;
			/**Weight for each affected vertex*/
			std::pair<unsigned int,float>* mptWeights;
			unsigned int muiWeightsAmount;
			unsigned int muiTransformationsAmount;
		};
	}
}

#endif //__BONE_H__