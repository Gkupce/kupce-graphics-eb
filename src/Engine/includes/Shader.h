#ifndef __SHADER_H__
#define __SHADER_H__
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

namespace Stu
{
	namespace Engine
	{
		class Renderer;

		class Shader
		{
		public:
			Shader();
			void Construct(Renderer* renderer);
			~Shader();
			IDirect3DVertexShader9* GetVtxShaderHandle() const;
			IDirect3DPixelShader9* GetPixShaderHandle() const;
			LPD3DXCONSTANTTABLE GetVtxConstantTable() const;
			LPD3DXCONSTANTTABLE GetPixConstantTable() const;
			D3DVERTEXELEMENT9* GetVertexElements() const;

			virtual const char* GetWVPMatrixName() const = 0;
		protected:
			virtual D3DVERTEXELEMENT9* GetVertexDefinition() const = 0;
			virtual const char* GetPixelShaderCode() const = 0;
			virtual const char* GetVertexShaderCode() const = 0;
			virtual const char* GetPixelShaderEntry() const = 0;
			virtual const char* GetVertexShaderEntry() const = 0;
			const std::string ReadFile(const char * fileName);

			D3DVERTEXELEMENT9 SetVtxElement(BYTE method, WORD offset, WORD stream, BYTE type, BYTE usage, BYTE usageIndex) const;
		private:
			IDirect3DVertexShader9* mptVtxShader;
			IDirect3DPixelShader9* mptPixShader;
			LPD3DXCONSTANTTABLE mptConstantTableVtx;
			LPD3DXCONSTANTTABLE mptConstantTablePix;
			D3DVERTEXELEMENT9* mptVertexElems;
		};
	}
}

#endif