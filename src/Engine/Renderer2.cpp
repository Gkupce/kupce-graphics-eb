
#include <d3d9.h>
#include <d3dx9.h>

#include "includes\VertexBuffer3D.h"
#include "includes\IndexBuffer3D.h"
#include "includes\Material.h"
#include "includes\Shader.h"
#include "includes\AnimationShader.h"
#include "includes\Renderer.h"

//----------------------------------------------------
//Dirty globals
D3DTRANSFORMSTATETYPE matrixModes[];// = {D3DTS_VIEW, D3DTS_WORLD, D3DTS_PROJECTION};
D3DPRIMITIVETYPE primitives[];// = {D3DPT_POINTLIST, D3DPT_LINELIST, D3DPT_LINESTRIP, D3DPT_TRIANGLELIST, D3DPT_TRIANGLESTRIP, D3DPT_TRIANGLEFAN};
//------------------------------------------------------------------------------------------------------------------------------------------------
//Shader stuff

bool Stu::Engine::Renderer::AddVertexShader(const char* shaderCode, const char* entryPoint, IDirect3DVertexShader9** vertexShader, LPD3DXCONSTANTTABLE* constantTable)
{
	HRESULT hr;
	LPD3DXBUFFER shaderBuffer, errors;

	hr = D3DXCompileShader(shaderCode, strlen(shaderCode), NULL, NULL, entryPoint, D3DXGetVertexShaderProfile(mhtDevice), 0, &shaderBuffer, &errors, constantTable);
	
	if(hr != D3D_OK)
	{
		const char* error = (const char*)errors->GetBufferPointer();
		return true;
	}

	hr = mhtDevice->CreateVertexShader((DWORD*)shaderBuffer->GetBufferPointer(), vertexShader);
	shaderBuffer->Release();
	return hr != D3D_OK;
}

bool Stu::Engine::Renderer::AddPixelShader(const char* shaderCode, const char* entryPoint, IDirect3DPixelShader9** pixelShader, LPD3DXCONSTANTTABLE* constantTable)
{
	HRESULT hr;
	LPD3DXBUFFER shaderBuffer, errors;
	
	hr = D3DXCompileShader(shaderCode, strlen(shaderCode), NULL, NULL, entryPoint, D3DXGetPixelShaderProfile(mhtDevice), 0, &shaderBuffer, &errors, constantTable);
	
	if(hr != D3D_OK)
	{
		return true;
	}

	hr = mhtDevice->CreatePixelShader((DWORD*)shaderBuffer->GetBufferPointer(), pixelShader);
	shaderBuffer->Release();
	
	return hr != D3D_OK;
}

bool Stu::Engine::Renderer::SetShader(Shader* shader)
{
	D3DXMATRIX tempMat, tempMat2;
	D3DXHANDLE hVSConst = NULL;
	//Set shaders proper
	mhtDevice->SetVertexShader(shader->GetVtxShaderHandle());
	mhtDevice->SetPixelShader(shader->GetPixShaderHandle());

	IDirect3DVertexDeclaration9* vertDeclaration = NULL;
	mhtDevice->CreateVertexDeclaration(shader->GetVertexElements(), &vertDeclaration);
	mhtDevice->SetVertexDeclaration(vertDeclaration);
	
	shader->GetVtxConstantTable()->SetDefaults(mhtDevice);
	hVSConst = shader->GetVtxConstantTable()->GetConstantByName(hVSConst, shader->GetWVPMatrixName());
	
	//prepare model view projection matrix
	mhtDevice->GetTransform(matrixModes[World], &tempMat);
	mhtDevice->GetTransform(matrixModes[View], &tempMat2);
	D3DXMatrixMultiply(&tempMat, &tempMat,&tempMat2);
	mhtDevice->GetTransform(matrixModes[Projection], &tempMat2);
	D3DXMatrixMultiply(&tempMat, &tempMat,&tempMat2);
	//Set mvp matrix
	shader->GetVtxConstantTable()->SetMatrix(mhtDevice, hVSConst, &tempMat);
	
	return false;
}

bool Stu::Engine::Renderer::Draw(VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer, IndexBuffer3D::Ptr indexBuffer, 
										DrawPrimitives primitive, Material mat, Frame3D* frame)
{
	if(!mpoAnimShader)
	{
		mpoAnimShader = new AnimationShader();
		if(!mpoAnimShader)
		{
			return true;
		}
		mpoAnimShader->Construct(this);
	}

	BindMaterial(mat);
	HRESULT hr = S_OK;
	//convert frame transformmation data to directx type
	D3DXMATRIX* transformations = NULL;
	transformations = new D3DXMATRIX[frame->numTransformations];
	if(!transformations)
	{
		return true;
	}
	for(unsigned int i = 0; i < frame->numTransformations; i++)
	{
		transformations[i] = D3DXMATRIX((const float*)frame->pTransformations[i].val);
	}

	SetShader(mpoAnimShader);
	D3DXHANDLE hVSConst = NULL;
	hVSConst = mpoAnimShader->GetVtxConstantTable()->GetConstantByName(hVSConst, "bones");
	mpoAnimShader->GetVtxConstantTable()->SetMatrixArray(mhtDevice, hVSConst, transformations, frame->numTransformations);

	mhtDevice->SetIndices(indexBuffer->GetIndexBuffer3D());
	vertexBuffer->Draw(primitives[primitive], indexBuffer->GetIndexCount());
	delete[] transformations;
	return false;
}

bool Stu::Engine::Renderer::InitVertexBuffer3D(VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer,
						 bool bDynamic, TexNormalAnimVertex * pVtxCollection, unsigned int uiVtxCount)
{
	return vertexBuffer->Create(mhtDevice, bDynamic, pVtxCollection, uiVtxCount);
}