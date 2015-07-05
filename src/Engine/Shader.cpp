#include "includes\Shader.h"
#include "includes\Renderer.h"

Stu::Engine::Shader::Shader()
{
	mptVtxShader = NULL;
	mptPixShader = NULL;
	mptConstantTableVtx = NULL;
	mptConstantTablePix = NULL;
	mptVertexElems = NULL;
}

void Stu::Engine::Shader::Construct(Renderer* renderer)
{
	renderer->AddVertexShader(GetVertexShaderCode(), GetVertexShaderEntry(), &mptVtxShader, &mptConstantTableVtx);
	renderer->AddPixelShader(GetPixelShaderCode(), GetPixelShaderEntry(), &mptPixShader,  &mptConstantTablePix);
	mptVertexElems = this->GetVertexDefinition();
}

Stu::Engine::Shader::~Shader()
{
	if(mptVtxShader)
	{
		mptVtxShader->Release();
		mptVtxShader = NULL;
	}
	if(mptPixShader)
	{
		mptPixShader->Release();
		mptPixShader = NULL;
	}
	if(mptConstantTableVtx)
	{
		mptConstantTableVtx->Release();
		mptConstantTableVtx = NULL;
	}
	if(mptConstantTablePix)
	{
		mptConstantTablePix->Release();
		mptConstantTablePix = NULL;
	}
	if(mptVertexElems)
	{
		delete[] mptVertexElems;
		mptVertexElems = NULL;
	}
}

IDirect3DVertexShader9* Stu::Engine::Shader::GetVtxShaderHandle() const
{
	return mptVtxShader;
}
IDirect3DPixelShader9* Stu::Engine::Shader::GetPixShaderHandle() const
{
	return mptPixShader;
}

LPD3DXCONSTANTTABLE Stu::Engine::Shader::GetVtxConstantTable() const
{
	return mptConstantTableVtx;
}

LPD3DXCONSTANTTABLE Stu::Engine::Shader::GetPixConstantTable() const
{
	return mptConstantTablePix;
}

D3DVERTEXELEMENT9* Stu::Engine::Shader::GetVertexElements() const
{
	return mptVertexElems;
}

D3DVERTEXELEMENT9 Stu::Engine::Shader::SetVtxElement(BYTE method, WORD offset, WORD stream, BYTE type, BYTE usage, BYTE usageIndex) const
{
	D3DVERTEXELEMENT9 result;
	result.Method = method;
	result.Offset = offset;
	result.Stream = stream;
	result.Type = type;
	result.Usage = usage;
	result.UsageIndex = usageIndex;
	return result;
}