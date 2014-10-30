#ifndef __VERTEXBUFFER3D_H
#define __VERTEXBUFFER3D_H
//--------------------------------------------------------------------------------
#include <D3D9.h>
#include "Defines.h"
//--------------------------------------------------------------------------------
//#pragma comment (lib, "d3d9.lib")
//--------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
class VertexBuffer3D
{
public:
	VertexBuffer3D();	
	~VertexBuffer3D();

	bool Create(IDirect3DDevice9 * pDev, bool bDynamic, PixelFormatClass * pVtxCollection, unsigned int uiVtxCount);
	void Bind(void);
	void Draw(D3DPRIMITIVETYPE primitiveType, unsigned int uiDrawUntil);
	unsigned int GetFVF();

	//Shared pointer declaration.
	typedef boost::shared_ptr<VertexBuffer3D<PixelFormatClass,FVF>> Ptr;
	//For some reason the SHARED_PTR macro does not compile.
	//SHARED_PTR(VertexBuffer3D<PixelFormatClass,FVF>) Ptr;
//--------------------------------------------------------------------------------
private:
	unsigned int m_uiVbSize;

	IDirect3DVertexBuffer9* m_pkVertexBuffer;
	IDirect3DDevice9* m_pkDevice;
};
//--------------------------------------------------------------------------------
#include "VertexBuffer3D.inl"
//--------------------------------------------------------------------------------
#endif //VERTEXBUFFER_H