template <class PixelFormatClass, unsigned int FVF>
inline VertexBuffer3D<PixelFormatClass, FVF>::VertexBuffer3D()
/*
:
m_uiVbSize(450),
m_uiFlush(150),
m_uiBase(0),
m_uiVtxToLock(0),
m_kPrimitiveType(NULL),
m_pkVertexBuffer(NULL),
m_pkDevice(NULL)
*/
{
	m_pkVertexBuffer=NULL;
	m_pkDevice=NULL;

}
//--------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
inline VertexBuffer3D<PixelFormatClass, FVF>::~VertexBuffer3D()
{

}
//--------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
inline bool VertexBuffer3D<PixelFormatClass, FVF>::Create(IDirect3DDevice9 * pDev, bool bDynamic, PixelFormatClass * pVtxCollection, unsigned int uiVtxCount)
{
	m_uiVbSize = uiVtxCount;
	m_pkVertexBuffer = NULL;
	m_pkDevice = pDev;

	// Creo el vertex buffer con los datos indicados
	HRESULT hr = pDev->CreateVertexBuffer(
						m_uiVbSize * sizeof(PixelFormatClass),
						(bDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : 0),
						FVF,
						D3DPOOL_DEFAULT,
						&m_pkVertexBuffer,
						NULL);
	// Indico que la base de vb a lockear es cero
	
	if (hr != D3D_OK)
		return true;

	void* pvVertices = NULL;
	hr = m_pkVertexBuffer->Lock(0, m_uiVbSize * sizeof(PixelFormatClass),
								(void **) &pvVertices, D3DLOCK_DISCARD);

	if (hr != D3D_OK)
		return true;

	memcpy(pvVertices, pVtxCollection,sizeof(PixelFormatClass)*uiVtxCount);
	m_pkVertexBuffer->Unlock();

	return false;
}
//--------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
inline void VertexBuffer3D<PixelFormatClass, FVF>::Draw(D3DPRIMITIVETYPE primitiveType, unsigned int uiDrawUntil)
{
	m_pkDevice->SetVertexShader(NULL);
	m_pkDevice->SetFVF(FVF);
	m_pkDevice->SetStreamSource(0, m_pkVertexBuffer, NULL, sizeof(PixelFormatClass));

	int iPrimitiveCount;
	// Determino la cantidad de primitivas a realizar en función del tipo
	if (primitiveType == D3DPT_POINTLIST)
		iPrimitiveCount = uiDrawUntil;
	else if (primitiveType == D3DPT_LINELIST)
		iPrimitiveCount = uiDrawUntil/2;
	else if (primitiveType == D3DPT_LINESTRIP)
		iPrimitiveCount = uiDrawUntil-1;
	else if (primitiveType == D3DPT_TRIANGLELIST)
		iPrimitiveCount = uiDrawUntil/3;
	else if (primitiveType == D3DPT_TRIANGLESTRIP)
		iPrimitiveCount = uiDrawUntil-2;
	else if (primitiveType == D3DPT_TRIANGLEFAN)
		iPrimitiveCount = uiDrawUntil-1;
	else
		iPrimitiveCount = 0;
	
	HRESULT hr = m_pkDevice->DrawIndexedPrimitive(primitiveType, 0, 0, m_uiVbSize, 0,iPrimitiveCount);
}
//--------------------------------------------------------------------------------
template <class PixelFormatClass, unsigned int FVF>
inline unsigned int VertexBuffer3D<PixelFormatClass, FVF>::GetFVF()
{
	return FVF;
}