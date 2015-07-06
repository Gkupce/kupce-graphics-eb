#ifndef __ANIMATEDMESH_H__
#define __ANIMATEDMESH_H__

#include <string>

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
		
		class ENGINE_API AnimatedMesh : public Entity
		{
		public:
			AnimatedMesh(Renderer* renderer, aiMesh* importMesh, Texture::Ptr tex);
			AnimatedMesh();
			AnimatedMesh(const char* name);
			AnimatedMesh(std::string name);
			~AnimatedMesh();

			virtual void Clone(const Node* original);
			virtual AnimatedMesh* Clone() const;
			virtual bool Draw(Renderer* renderer);

			void SetMaterial(const Material material);
			Material GetMaterial() const;

		private:
			IndexBuffer3D::Ptr mpoIndexBuffer;
			VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>::Ptr mpoVertexBuffer;
			Texture::Ptr mpoTexture;
			Material moMaterial;

			std::string animation;
			float mfTime;
			bool mbPlaying;
			float mfSpeed;
		};
	}
}

#endif // __ANIMATEDMESH_H__