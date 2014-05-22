#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <d3d9.h>
#include <d3dx9.h>

#include "Structs.h"

template <class PixelFormatClass, unsigned int FVF>
class VertexBuffer;

namespace Stu
{
	namespace Engine
	{

		enum MatrixMode
		{
			View = 0,
			World = 1,
			Projection = 2
		};

		enum DrawPrimitives
		{
			PointList = 0,
			LineList = 1,
			LineStrip = 2,
			TriangleList = 3,
			TriangleStrip = 4,
			TriangleFan = 5
		};

		class Window;

		class Renderer
		{
		private:
			IDirect3DDevice9* mhtDevice;
			Color mtClearColor;
			VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZ>* mpoColorVtxBuffer;
			VertexBuffer<TexVertex, D3DFVF_TEX1 | D3DFVF_XYZ>* mpoTexVtxBuffer;
			//VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZRHW>* mpoColorVtxBuffer;

			D3DTRANSFORMSTATETYPE mtMatrixMode;
			
			D3DXMATRIX mtProjectionMat;
			D3DXVECTOR3 mtViewerUp, mtViewerPos;

			
			void SetMatrixMode(D3DTRANSFORMSTATETYPE tMatrixMode);//Matrix_Mode mode
			void SetViewportPosition();

		public:
			Renderer();
			~Renderer();

			void SetMatrixMode(MatrixMode eMatrixMode);
			void LoadIdentity();
			void Translate(float x, float y, float z);
			void Scale(float x, float y);
			void RotateX(float angle);
			void RotateY(float angle);
			void RotateZ(float angle);
			bool Draw(ColorVertex* vertexs, unsigned int vertexCount, DrawPrimitives primitive);
			bool Draw(TexVertex* vertexs, unsigned int vertexCount, DrawPrimitives primitive);
			bool Init(Window* poWindow);//returns wether there was an error (true) or not (false)
			void SetClearColor(unsigned long clearColor); //0xaarrggbb
			void SetClearColor(char a, char r, char g, char b);
			unsigned long GetClearColor(); //0xaarrggbb
			void GetClearColor(char* a, char* r, char* g, char* b);
			void StartFrame();
			void EndFrame();
			void LoadTexture(char* path, Color colorKey);
			void LoadTexture();
		};
	}
}

#include "Renderer.inl"
#endif //__RENDERER_H__