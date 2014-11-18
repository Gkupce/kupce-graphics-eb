#ifndef __MESH_H__
#define __MESH_H__

#include "defines.h"
#include "Entity.h"
#include "IndexBuffer3D.h"
#include "VertexBuffer3D.h"
#include "Renderer.h"
#include "Texture.h"
#include "Material.h"

struct aiMesh;

namespace Stu
{
	namespace Engine
	{
		
		class ENGINE_API Mesh : public Entity
		{
		public:
			Mesh(Renderer* renderer, aiMesh* importMesh, Texture::Ptr tex);
			Mesh();
			Mesh(const char* name);
			Mesh(std::string name);
			~Mesh();

			virtual void Clone(const Node* original);
			virtual Mesh* Clone() const;
			virtual bool Draw(Renderer* renderer);

			void SetMaterial(const Material material);
			Material GetMaterial() const;

		private:
			IndexBuffer3D::Ptr mpoIndexBuffer;
			VertexBuffer3D<TexNormalVertex, TEXTURE_NORMAL_VERTEX>::Ptr mpoVertexBuffer;
			Texture::Ptr mpoTexture;
			Material moMaterial;
		};
	}
}

#endif