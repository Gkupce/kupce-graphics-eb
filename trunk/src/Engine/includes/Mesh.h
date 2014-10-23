#ifndef __MESH_H__
#define __MESH_H__

#include "defines.h"
#include "Entity.h"
#include "IndexBuffer3D.h"
#include "VertexBuffer3D.h"
#include "Renderer.h"
#include "Texture.h"

struct aiMesh;

namespace Stu
{
	namespace Engine
	{
		
		class ENGINE_API Mesh : public Entity
		{
		public:
			Mesh(Renderer* renderer, aiMesh* importMesh, Texture::Ptr tex);
			~Mesh();

			virtual bool Draw(Renderer* renderer);


		private:
			IndexBuffer3D* mpoIndexBuffer;
			VertexBuffer3D<TexVertex, TEXTURE_VERTEX>* mpoVertexBuffer;
			Texture::Ptr mpoTexture;
		};
	}
}

#endif