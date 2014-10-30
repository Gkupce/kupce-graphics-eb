#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <string>

#include "defines.h"
#include "Vector3.h"

namespace Stu
{
	namespace Engine
	{
		class Renderer;
		class Game;
		class Scene;

		class ENGINE_API Node
		{
		public:

			Node();
			Node(std::string name);
			Node(const char* name);
			~Node();

			const Vector3 GetPosition() const;
			void SetPosition(Vector3 position);
			void SetPosition(float x, float y, float z);
			const Vector3 GetRotation() const;
			void SetRotation(Vector3 rotation);
			void SetRotation(float x, float y, float z);
			const Vector3 GetScale() const;
			void SetScale(Vector3 scale);
			void SetScale(float x, float y, float z);
			Node* GetParent();
			Node* GetChild(int child);
			int GetChildCount() const;
			void SetName(const std::string name);
			void SetName(const char *name);
			const std::string GetName() const;

			void AddChild(Node* child);
			void RemoveChild(int child);
			void RemoveChild(Node* child);
			void RemoveFromScene();
			void SetParent(Node* parent);

			virtual void Update(float deltaTime);
			virtual void OnCollision(Node* other);

			void SetUpdateable(bool state);
			bool IsUpdateable() const;

			virtual void UpdateHierarchy(float deltaTime);
			virtual bool DrawHierarchy(Renderer* renderer);
			bool CollidesWith(Node* other);
			void SetTransformations(Renderer* renderer);
		protected:
			void CreateAABB(Vector3 max, Vector3 min);

		private:
			friend Game;
			void AddChildInt(Node* child);
			void SetParentInt(Node* parent);
			void RemoveChildInt(Node* child);
			void Initialize();

			std::string moName;
			std::vector<Node*> moChildren;
			Node* mpoParent;

			bool mbUpdateable;

			Vector3 moPosition;
			Vector3 moRotation;
			Vector3 moScale;
			
			Vector3 moMaxCoord;
			Vector3 moMinCoord;

			friend class Scene;
			friend class Game;
		};
	}
}

#include "Scene.h"
#include "Node.inl"

#endif