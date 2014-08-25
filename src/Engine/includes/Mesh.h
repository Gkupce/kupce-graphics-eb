#ifndef __MESH_H__
#define __MESH_H__

#include "defines.h"
#include "Entity.h"
#include "IndexBuffer3D.h"
#include "VertexBuffer3D.h"
#include "Renderer.h"


namespace Stu
{
	namespace Engine
	{
		class ENGINE_API Mesh : Entity
		{
		public:
			Mesh(Renderer* renderer);
			~Mesh();

			virtual bool Draw(Renderer* renderer);


		private:
			IndexBuffer3D* mpoIndexBuffer;
			VertexBuffer3D<ColorVertex, COLOR_VERTEX>* mpoVertexBuffer;
		};
	}
}

#endif