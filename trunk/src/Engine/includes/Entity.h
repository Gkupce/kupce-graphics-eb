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
			Entity(const char* name);
			Entity(std::string name);
			~Entity();

			virtual bool DrawHierarchy(Renderer* renderer);
			virtual bool Draw(Renderer* renderer);

		private:
			void Initialize();
		};
	}
}

#endif //__ENTITY_H__
