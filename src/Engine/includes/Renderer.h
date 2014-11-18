#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <vector>

#include <d3d9.h>
#include <d3dx9.h>

#include "Structs.h"
#include "VertexBuffer3D.h"
#include "IndexBuffer3D.h"

#define COLOR_VERTEX D3DFVF_DIFFUSE | D3DFVF_XYZ
#define TEXTURE_VERTEX D3DFVF_TEX1 | D3DFVF_XYZ
#define TEXTURE_NORMAL_VERTEX D3DFVF_TEX1 | D3DFVF_XYZ | D3DFVF_NORMAL

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
		class Camera;
		class Vector3;
		class Quaternion;
		class Material;
		class Light;

		class Renderer
		{
		private:
			unsigned long mulLightAmnt;

			IDirect3DDevice9* mhtDevice;
			Color mtClearColor;
			VertexBuffer<ColorVertex, COLOR_VERTEX>* mpoColorVtxBuffer;
			VertexBuffer<TexVertex, TEXTURE_VERTEX>* mpoTexVtxBuffer;
			//VertexBuffer<ColorVertex, D3DFVF_DIFFUSE | D3DFVF_XYZRHW>* mpoColorVtxBuffer;
			std::vector<LPDIRECT3DTEXTURE9> moTextureVec;

			D3DTRANSFORMSTATETYPE mtMatrixMode;
			
			D3DXMATRIX mtProjectionMat;
			D3DXVECTOR3 mtViewerUp, mtViewerPos;

			
			void SetMatrixMode(D3DTRANSFORMSTATETYPE tMatrixMode);//Matrix_Mode mode
			void SetViewportPosition();
			
			D3DMATERIAL9 ConvertMaterial(Material mat);
			D3DCOLORVALUE ConvertColor(Color col);
			D3DLIGHT9 ConvertLight(Light light);

		public:
			Renderer();
			~Renderer();

			void SetViewportPosition(Camera* camera);
			void SetMatrixMode(MatrixMode eMatrixMode);
			void LoadIdentity();
			void Translate(float x, float y, float z);
			void Scale(float x, float y, float z);
			void RotateX(float angle);
			void RotateY(float angle);
			void RotateZ(float angle);
			void Rotate(Quaternion baseRot, Vector3 eulerRot);
			bool Draw(ColorVertex* vertexs, unsigned int vertexCount, DrawPrimitives primitive);
			bool Draw(TexVertex* vertexs, unsigned int vertexCount, DrawPrimitives primitive);
			
			
			bool Draw(VertexBuffer3D<ColorVertex, COLOR_VERTEX>::Ptr vertexBuffer, IndexBuffer3D::Ptr indexBuffer, 
								DrawPrimitives primitive, Material mat);
			bool Draw(VertexBuffer3D<TexNormalVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer, IndexBuffer3D::Ptr indexBuffer, 
								DrawPrimitives primitive, Material mat);

			bool Init(Window* poWindow);//returns wether there was an error (true) or not (false)
			void SetClearColor(unsigned long clearColor); //0xaarrggbb
			void SetClearColor(char a, char r, char g, char b);
			unsigned long GetClearColor(); //0xaarrggbb
			void GetClearColor(char* a, char* r, char* g, char* b);
			void StartFrame();
			void EndFrame();
			int LoadTexture(const char* path, Color colorKey, unsigned int& width, unsigned int& height);
			bool BindTexture(int texCode);
			void UnbindTexture();
			bool BindMaterial(Material mat);
			void UnbindMaterial();

			bool InitVertexBuffer3D(VertexBuffer3D<ColorVertex, COLOR_VERTEX>::Ptr vertexBuffer,
						 bool bDynamic, ColorVertex * pVtxCollection, unsigned int uiVtxCount);
			bool InitVertexBuffer3D(VertexBuffer3D<TexNormalVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer,
						 bool bDynamic, TexNormalVertex * pVtxCollection, unsigned int uiVtxCount);
			bool InitIndexBuffer3D(IndexBuffer3D::Ptr indexBuffer, bool bDynamic, 
									DWORD* pkIndexColection, size_t iIndexCount);

			void SetLight(Light light);
			void ChangeLightState(Light light);
			void ChangeLightState(Light light, bool state);
		};
	}
}

#include "Renderer.inl"
#endif //__RENDERER_H__