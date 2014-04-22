#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <d3d9.h>
#include <d3dx9.h>

template <class PixelFormatClass, unsigned int FVF>
class VertexBuffer;

namespace Stu
{
	namespace Engine
	{
		struct ColorVertex;
		class Window;

		class Renderer
		{
		private:
			IDirect3DDevice9* mhtDevice;
			D3DCOLOR mulClearColor; //unsigned long 0xaarrggbb
			VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZ>* mpoColorVtxBuffer;

			D3DTRANSFORMSTATETYPE mtMatrixMode;
			
			D3DXMATRIX mtProjectionMat;
			D3DXVECTOR3 mtViewerUp, mtViewerPos;

			
			void SetMatrixMode(D3DTRANSFORMSTATETYPE tMatrixMode);//Matrix_Mode mode
			void SetViewportPosition();

		public:
			Renderer();
			~Renderer();

			void LoadIdentity();
			void Translate(float x, float y, float z);
			void Scale(float x, float y);
			void RotateX(float angle);
			void RotateY(float angle);
			void RotateZ(float angle);
			bool Draw(ColorVertex* vertexs, unsigned int vertexCount);
			bool Init(Window* poWindow);//returns wether there was an error (true) or not (false)
			void SetClearColor(unsigned long clearColor); //0xaarrggbb
			void SetClearColor(int a, int r, int g, int b);
			unsigned long GetClearColor(); //0xaarrggbb
			void StartFrame();
			void EndFrame();

		};
	}
}

#include "Renderer.inl"
#endif //__RENDERER_H__