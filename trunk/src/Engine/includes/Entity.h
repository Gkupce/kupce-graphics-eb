#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		class Renderer;
		class Game;
		class AABB2D;

		class ENGINE_API Entity
		{
		public:
			Entity();
			~Entity();

			Vector3 GetPosition() const;
			void SetPosition(Vector3 position);
			void SetPosition(float x, float y, float z);
			Vector3 GetRotation() const;
			void SetRotation(Vector3 rotation);
			void SetRotation(float x, float y, float z);
			Vector3 GetScale() const;
			void SetScale(Vector3 scale);
			void SetScale(float x, float y, float z);
			
			void SetAddedToDrawables(bool state);
			bool IsAddedToDrawables() const;
			
			void SetUpdateable(bool state);
			bool IsUpdateable() const;
			bool CollidesWith(Entity* other);
			
			virtual void Update(float deltaTime);
			virtual void OnCollision(Entity* other);
			virtual bool Draw(Renderer* renderer);
		
		protected:
			void CreateAABB(Vector3 max, Vector3 min);
		private:
			bool mbAddedToDrawables;
			bool mbUpdateable;
			Vector3 moPosition;
			Vector3 moRotation;
			Vector3 moScale;
			Vector3 moMaxCoord;
			Vector3 moMinCoord;
		};
	}
}

#include "Entity.inl"

#endif //__ENTITY_H__
