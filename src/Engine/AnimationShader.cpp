#include "includes\AnimationShader.h"

Stu::Engine::AnimationShader::AnimationShader() : Shader()
{
	
}

D3DVERTEXELEMENT9* Stu::Engine::AnimationShader::GetVertexDefinition() const
{
	const unsigned int amount = 6;
	D3DVERTEXELEMENT9* vertexElems = NULL;
	vertexElems = new D3DVERTEXELEMENT9[amount];
	if(!vertexElems)
	{
		throw "VertexElement could not be initialized";
	}

	ZeroMemory(vertexElems, sizeof(D3DVERTEXELEMENT9)*amount);

	//pos
	vertexElems[0] = SetVtxElement(D3DDECLMETHOD_DEFAULT, 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLUSAGE_POSITION, 0);
	
	//normal
	vertexElems[1] = SetVtxElement(D3DDECLMETHOD_DEFAULT, sizeof(float) * 3, 0, D3DDECLTYPE_FLOAT3, D3DDECLUSAGE_NORMAL, 0);


	//tex UV
	vertexElems[2] = SetVtxElement(D3DDECLMETHOD_DEFAULT, sizeof(float) * 6, 0, D3DDECLTYPE_FLOAT2, D3DDECLUSAGE_TEXCOORD, 0);

	//Bone weights
	vertexElems[3] = SetVtxElement(D3DDECLMETHOD_DEFAULT, sizeof(float) * 8, 0, D3DDECLTYPE_FLOAT4, D3DDECLUSAGE_BLENDWEIGHT, 0);

	//Bone indexes
	vertexElems[4] = SetVtxElement(D3DDECLMETHOD_DEFAULT, sizeof(float) * 12, 0, D3DDECLTYPE_UBYTE4, D3DDECLUSAGE_BLENDINDICES, 0);

	//End
	vertexElems[5] = SetVtxElement(D3DDECLMETHOD_DEFAULT, 0, 0xFF, D3DDECLTYPE_UNUSED, 0, 0);

	return vertexElems;
}

const char* Stu::Engine::AnimationShader::GetPixelShaderCode() const
{
	const char* code =
		"struct v2p {\n"
		"	float4 Position	: POSITION;\n"
		"	float2 Texcoord	: TEXCOORD0;\n"
		"};\n"
		"struct p2f {\n"
		"	float4 Color	: COLOR;\n"
		"};\n"
		"texture ColorTexture : DIFFUSE <\n"
		"    string ResourceType = \"2D\";\n"
		">;\n"
		"sampler2D TexSampler = sampler_state {\n"
		"    Texture = <ColorTexture>;\n"
		"    FILTER = MIN_MAG_MIP_LINEAR;\n"
		"    AddressU = Wrap;\n"
		"    AddressV = Wrap;\n"
		"};\n"
		"void mainPS(v2p IN, out p2f OUT)\n"
		"{\n"
		"	OUT.Color = tex2D(TexSampler, IN.Texcoord);\n"
		"}\n";
	
	return code;
}

const char* Stu::Engine::AnimationShader::GetVertexShaderCode() const
{
	const char* code =
		"struct a2v{\n"
		"	float4 boneIndex0 : BLENDINDICES0;\n"
		
		"	float4 boneWeight0 : BLENDWEIGHT0;\n"
		
		"	float3 normal : NORMAL0;\n"
		"	float3 pos : POSITION0;\n"
		"	float2 texcoord : TEXCOORD0;\n"
		"};\n"
		"struct v2p {\n"
		"	float4 pos : POSITION;\n"
		"	float2 texcoord : TEXCOORD0;\n"
		"};\n"
		
		"static const int MAX_MATRICES = 50; // Max matrices per batch\n"
		"float4x4 bones[MAX_MATRICES] : BONESARRAY; // bones Array (please let this work)\n"
		
		"float4x4 mvm : WorldViewProjection;\n"
		"void mainVS(a2v IN, out v2p OUT)\n"
		"{\n"
		"	float4 alteredPos = float4(IN.pos, 1.0);\n"
		"	for(int i = 0; i < 4; i++)\n"
		"	{\n"
		"		if(IN.boneIndex0[i] > MAX_MATRICES) break;"
		"		alteredPos = mul(alteredPos, bones[IN.boneIndex0[i]] * IN.boneWeight0[i]);\n"
		"	}\n"
		"	OUT.pos = mul(float4(IN.pos,1), mvm);\n"
		//"	OUT.pos = mul(alteredPos, mvm);\n"
		"	OUT.texcoord = IN.texcoord;\n"
		"}";
		
		return code;
}

const char* Stu::Engine::AnimationShader::GetPixelShaderEntry() const
{
	return "mainPS";
}

const char* Stu::Engine::AnimationShader::GetVertexShaderEntry() const
{
	return "mainVS";
}

const char* Stu::Engine::AnimationShader::GetWVPMatrixName() const
{
	return "mvm";
}
