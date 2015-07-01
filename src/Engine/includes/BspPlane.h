#ifndef __BSPPLANE_H__
#define __BSPPLANE_H__
#include "Node.h"

namespace Stu
{
	namespace Engine
	{
		class ENGINE_API BspPlane : public Node
		{
		public:
			BspPlane(Vector3 normal, Vector3 point);
			BspPlane(Vector3 normal, Vector3 point, const char* name);
			BspPlane(Vector3 normal, Vector3 point, std::string name);
			int checkSide(const Node* node) const;
			int checkSide(const BspPlane* plane) const;
		private:
			Vector3 moNormal;
			Vector3 moPoint;
		};
	}
}
#endif //__BSPPLANE_H__