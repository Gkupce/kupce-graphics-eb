#ifndef __ENTITY2D_H__
#define __ENTITY2D_H__

#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		class Renderer;

		class ENGINE_API Entity2D
		{
		private:
			Vector3 moPosition;
			Vector3 moRotation;
			Vector3 moScale;
		public:
			Entity2D();
			~Entity2D();

			Vector3 GetPosition();
			void SetPosition(Vector3 position);
			Vector3 GetRotation();
			void SetRotation(Vector3 rotation);
			Vector3 GetScale();
			void SetScale(Vector3 scale);

			virtual bool Draw(Renderer* renderer);
		};
	}
}

#include "Entity2D.inl"

#endif //__ENTITY2D_H__