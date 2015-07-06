#ifndef __COLLISIONMASTER_H__
#define __COLLISIONMASTER_H__

struct D3DXMATRIX;

namespace Stu
{
	namespace Engine
	{
		class CollisionMaster
		{
		public:
			
			static D3DXMATRIX GetFinalPosition(const Node* node);
			static bool NodeCollisions(const Node* first, const Node* second);
			static int NodePlaneCollisions(const Node* node, const BspPlane* plane);
			static int PlaneCollisions(const BspPlane* first, const BspPlane* second);
		private:

		};
	}
}

#endif //__COLLISIONMASTER_H__