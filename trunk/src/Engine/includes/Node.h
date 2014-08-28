#ifndef __NODE_H__
#define __NODE_H__

#include <vector>

#include "defines.h"
#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		class Renderer;

		class ENGINE_API Node
		{
		public:

			Node();
			~Node();

			Vector3 GetPosition() const;
			void SetPosition(Vector3 position);
			void SetPosition(float x, float y, float z);
			Vector3 GetRotation() const;
			void SetRotation(Vector3 rotation);
			void SetRotation(float x, float y, float z);
			Vector3 GetScale() const;
			void SetScale(Vector3 scale);
			void SetScale(float x, float y, float z);
			
			virtual void Update(float deltaTime);
			virtual void OnCollision(Node* other);

			void SetUpdateable(bool state);
			bool IsUpdateable() const;

			virtual bool DrawHierarchy(Renderer* renderer);
			bool CollidesWith(Node* other);
			void SetTransformations(Renderer* renderer);
		protected:
			void CreateAABB(Vector3 max, Vector3 min);

		private:
			std::vector<Node*> moChildren;
			Node* mpoParent;

			bool mbUpdateable;

			Vector3 moPosition;
			Vector3 moRotation;
			Vector3 moScale;
			
			Vector3 moMaxCoord;
			Vector3 moMinCoord;
		};
	}
}

#include "Node.inl"

#endif