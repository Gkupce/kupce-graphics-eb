#ifndef __ANIMATIONSHADER_H__
#define __ANIMATIONSHADER_H__
#include <d3d9.h>
#include <d3dx9.h>
#include "Shader.h"

namespace Stu
{
	namespace Engine
	{
		class AnimationShader : public Shader
		{
		public:
			AnimationShader();

			virtual const char* GetWVPMatrixName() const;

		protected:
			virtual D3DVERTEXELEMENT9* GetVertexDefinition() const;
			virtual const char* GetPixelShaderCode() const;
			virtual const char* GetVertexShaderCode() const;
			virtual const char* GetPixelShaderEntry() const;
			virtual const char* GetVertexShaderEntry() const;
		};
	}
}


#endif //__ANIMATIONSHADER_H__