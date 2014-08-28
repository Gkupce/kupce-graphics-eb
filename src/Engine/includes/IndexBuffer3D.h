#ifndef INDEXBUFFER3D_H
#define INDEXBUFFER3D_H
//--------------------------------------------------------------------------------
#include <D3D9.h>
#include "Defines.h"
//--------------------------------------------------------------------------------
//#pragma comment (lib, "d3d9.lib")
//--------------------------------------------------------------------------------
class IndexBuffer3D
{
private:
	size_t m_iIndexCount;

	IDirect3DIndexBuffer9* m_pkIndexBuffer3D;
	IDirect3DDevice9* m_pkDevice;

	//DWORD* m_pkIndexColection;


//--------------------------------------------------------------------------------
public:
	
	IndexBuffer3D();	
	~IndexBuffer3D();

	bool Create(IDirect3DDevice9 * pDev, bool bDynamic, size_t iIndexCount, DWORD* pkIndexColection);
	IDirect3DIndexBuffer9* GetIndexBuffer3D();
	size_t GetIndexCount();

//--------------------------------------------------------------------------------
//friend class Renderer;
//--------------------------------------------------------------------------------
};
//--------------------------------------------------------------------------------
#include "IndexBuffer3D.inl"
//--------------------------------------------------------------------------------
#endif //INDEXBUFFER3D_H