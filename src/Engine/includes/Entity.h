#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Node.h"
#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		class Renderer;
		class Game;
		class AABB2D;

		class ENGINE_API Entity : public Node
		{
		public:
			Entity();
			~Entity();

			void SetAddedToDrawables(bool state);
			bool IsAddedToDrawables() const;
			
			virtual bool DrawHierarchy(Renderer* renderer);
			virtual bool Draw(Renderer* renderer);

		private:
			bool mbAddedToDrawables;
		};
	}
}

#include "Entity.inl"

#endif //__ENTITY_H__
