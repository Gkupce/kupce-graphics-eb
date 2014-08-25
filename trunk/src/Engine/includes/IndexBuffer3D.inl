inline IndexBuffer3D::IndexBuffer3D()
{
	m_pkIndexBuffer3D=NULL;
	m_pkDevice=NULL;

}
//--------------------------------------------------------------------------------
inline IndexBuffer3D::~IndexBuffer3D()
{

}
//--------------------------------------------------------------------------------
inline bool IndexBuffer3D::Create (IDirect3DDevice9 * pDev, bool bDynamic, 
								   size_t iIndexCount, DWORD* pkIndexColection)
{
	if (iIndexCount < 1)
		return false;

	m_iIndexCount = iIndexCount;

	m_pkIndexColection = pkIndexColection;

	m_pkDevice = pDev;

	// Creo el vertex buffer con los datos indicados
	HRESULT hr = pDev->CreateIndexBuffer(
						static_cast<UINT>(iIndexCount * sizeof(DWORD)),
						(bDynamic ? D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC : 0),
						D3DFMT_INDEX32,
						D3DPOOL_DEFAULT,
						&m_pkIndexBuffer3D,
						0);

	if (hr != D3D_OK)
		return false;

	void* pvIndices = NULL;

	hr = m_pkIndexBuffer3D->Lock(0,
								static_cast<UINT>(m_iIndexCount * sizeof(DWORD)),
								(void **) &pvIndices,
								D3DLOCK_DISCARD);

	memcpy(pvIndices, m_pkIndexColection, sizeof(DWORD) * m_iIndexCount);

	hr = m_pkIndexBuffer3D->Unlock();

	return true;
}
//--------------------------------------------------------------------------------
inline IDirect3DIndexBuffer9* IndexBuffer3D::getIndexBuffer3D()
{
	return m_pkIndexBuffer3D;
}
//--------------------------------------------------------------------------------
inline size_t IndexBuffer3D::getIndexCount()
{
	return m_iIndexCount;
}
//--------------------------------------------------------------------------------

