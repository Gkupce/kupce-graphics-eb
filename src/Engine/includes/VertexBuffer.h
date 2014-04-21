#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
//--------------------------------------------------------------------------------
#include <D3D9.h>
#include "Defines.h"
//--------------------------------------------------------------------------------
//#pragma comment (lib, "d3d9.lib")
//--------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
class VertexBuffer
{
private:
	unsigned int m_uiVbSize;
	unsigned int m_uiFlush;
	unsigned int m_uiBase;
	unsigned int m_uiVtxToLock;

	D3DPRIMITIVETYPE m_kPrimitiveType;
	IDirect3DVertexBuffer9* m_pkVertexBuffer;
	IDirect3DDevice9* m_pkDevice;


//--------------------------------------------------------------------------------
public:
	
	VertexBuffer();	
	~VertexBuffer();

	bool Create(IDirect3DDevice9 * pDev, bool bDynamic);
	void Bind(void);
	void Draw(PixelFormatClass * pVtxCollection, D3DPRIMITIVETYPE primitiveType, unsigned int uiVtxCount);
	void Flush();

};
//--------------------------------------------------------------------------------
#include "VertexBuffer.inl"
//--------------------------------------------------------------------------------
#endif //VERTEXBUFFER_H