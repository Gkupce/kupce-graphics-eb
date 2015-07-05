
#include <d3d9.h>
#include <d3dx9.h>

#include "includes\VertexBuffer3D.h"
#include "includes\IndexBuffer3D.h"
#include "includes\Material.h"
#include "includes\Shader.h"
#include "includes\Renderer.h"

//----------------------------------------------------
//Dirty globals
D3DTRANSFORMSTATETYPE matrixModes[];// = {D3DTS_VIEW, D3DTS_WORLD, D3DTS_PROJECTION};
D3DPRIMITIVETYPE primitives[];// = {D3DPT_POINTLIST, D3DPT_LINELIST, D3DPT_LINESTRIP, D3DPT_TRIANGLELIST, D3DPT_TRIANGLESTRIP, D3DPT_TRIANGLEFAN};
//------------------------------------------------------------------------------------------------------------------------------------------------
//Shader stuff
#include <iostream>

bool Stu::Engine::Renderer::AddVertexShader(const char* shaderCode, const char* entryPoint, IDirect3DVertexShader9** vertexShader, LPD3DXCONSTANTTABLE* constantTable)
{
	/*
	char* shaderCode = 
		"struct a2v{"
		"	float3 pos : POSITION0;"
		"	float3 normal : NORMAL0;"
		"	float2 texcoord : TEXCOORD0;"
		"};"
		"struct v2p {"
		"	float4 pos : POSITION0;"
		"	float2 texcoord : TEXCOORD0;"
		"	float4 normal : NORMAL0;"
		"};"
		"float4x4 mvm : WorldViewProjection;"
		"float val : MyVal;"
		"void mainVS(a2v IN, out v2p OUT)"
		"{"
		"	OUT.pos = mul(float4(IN.pos,1), mvm);"
		"	OUT.texcoord = IN.texcoord;"
		"	OUT.normal = float4(normalize(IN.normal), 1);"
		"}";
	*/
	HRESULT hr;
	LPD3DXBUFFER shaderBuffer, errors;

	hr = D3DXCompileShader(shaderCode, strlen(shaderCode), NULL, NULL, entryPoint, D3DXGetVertexShaderProfile(mhtDevice), 0, &shaderBuffer, &errors, constantTable);
	
	if(hr != D3D_OK)
	{
		return true;
	}

	hr = mhtDevice->CreateVertexShader((DWORD*)shaderBuffer->GetBufferPointer(), vertexShader);
	shaderBuffer->Release();
	return hr != D3D_OK;
	/*
	mptVertexElems = NULL;
	unsigned int amount = 4;
	mptVertexElems = new D3DVERTEXELEMENT9[amount];
	
	ZeroMemory(mptVertexElems, sizeof(D3DVERTEXELEMENT9)*amount);

	//pos
	mptVertexElems[0].Stream = 0;
	mptVertexElems[0].Offset = 0;
	mptVertexElems[0].Type = D3DDECLTYPE_FLOAT3;
	mptVertexElems[0].Method = 0;
	mptVertexElems[0].Usage = D3DDECLUSAGE_POSITION;
	mptVertexElems[0].UsageIndex = 0;
	
	//normal
	mptVertexElems[1].Stream = 0;
	mptVertexElems[1].Offset = sizeof(float) * 3;
	mptVertexElems[1].Type = D3DDECLTYPE_FLOAT3;
	mptVertexElems[1].Method = D3DDECLMETHOD_DEFAULT;
	mptVertexElems[1].Usage = D3DDECLUSAGE_NORMAL;
	mptVertexElems[1].UsageIndex = 0;

	//tex UV
	mptVertexElems[2].Stream = 0;
	mptVertexElems[2].Offset = sizeof(float) * 6;
	mptVertexElems[2].Type = D3DDECLTYPE_FLOAT2;
	mptVertexElems[2].Method = D3DDECLMETHOD_DEFAULT;
	mptVertexElems[2].Usage = D3DDECLUSAGE_TEXCOORD;
	mptVertexElems[2].UsageIndex = 0;
	//End
	mptVertexElems[3].Stream = 0xFF;
	mptVertexElems[3].Offset = 0;
	mptVertexElems[3].Type = D3DDECLTYPE_UNUSED;
	mptVertexElems[3].Method = D3DDECLMETHOD_DEFAULT;
	mptVertexElems[3].Usage = 0;
	mptVertexElems[3].UsageIndex = 0;
	*/
}

bool Stu::Engine::Renderer::AddPixelShader(const char* shaderCode, const char* entryPoint, IDirect3DPixelShader9** pixelShader, LPD3DXCONSTANTTABLE* constantTable)
{
	/*
	char* shaderCode =
		"struct v2p {"
		"	float4 normal : NORMAL0;"
		"	float2 texcoord	: TEXCOORD0;"
		"};"
		"struct p2f {"
		"	float4 color : COLOR;"
		"};"
		"texture ColorTexture : DIFFUSE <"
		"	string ResourceType = \"2D\";"
		">;"
		"sampler2D TexSampler = sampler_state {"
		"	Texture = <ColorTexture>;"
		"	FILTER = MIN_MAG_MIP_LINEAR;"
		"	AddressU = Wrap;"
		"	AddressV = Wrap;"
		"};"
		"void mainPS(v2p IN, out p2f OUT)"
		"{"
		"	OUT.color = saturate(tex2D(TexSampler, IN.texcoord));"
		"}";
	*/
	
	
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
	BindMaterial(mat);
	HRESULT hr = S_OK;
	
	//TODO SetShader(mpoAnimShader);
	//TODO SetFrameTFData
	mhtDevice->SetIndices(indexBuffer->GetIndexBuffer3D());
	vertexBuffer->Draw(primitives[primitive], indexBuffer->GetIndexCount());
	
	return false;
}

bool Stu::Engine::Renderer::InitVertexBuffer3D(VertexBuffer3D<TexNormalAnimVertex, TEXTURE_NORMAL_VERTEX>::Ptr vertexBuffer,
						 bool bDynamic, TexNormalAnimVertex * pVtxCollection, unsigned int uiVtxCount)
{
	return vertexBuffer->Create(mhtDevice, bDynamic, pVtxCollection, uiVtxCount);
}