struct a2v{
	unsigned int boneIndex0 : BLENDINDICES0;
	unsigned int boneIndex1 : BLENDINDICES1;
	unsigned int boneIndex2 : BLENDINDICES2;
	unsigned int boneIndex3 : BLENDINDICES3;
	unsigned int boneIndex4 : BLENDINDICES4;

	float boneWeight0 : BLENDWEIGHT0;
	float boneWeight1 : BLENDWEIGHT1;
	float boneWeight2 : BLENDWEIGHT2;
	float boneWeight3 : BLENDWEIGHT3;
	float boneWeight4 : BLENDWEIGHT4;

	float3 normal : NORMAL0;
	float3 pos : POSITION0;
	float2 texcoord : TEXCOORD0;
};
struct v2p {
	float4 pos : POSITION;
	float2 texcoord : TEXCOORD0;
};

static const int MAX_MATRICES = 255; // Max matrices per batch
float4x4 bones[MAX_MATRICES] : BONESARRAY; // bones Array (please let this work)

float4x4 mvm : WorldViewProjection;
void mainVS(a2v IN, out v2p OUT)
{
	vector<float, 5> weights = {boneWeight0, boneWeight1, boneWeight2, boneWeight3, boneWeight4};
	vector<unsigned int, 5> boneIndexes = {boneIndex0, boneIndex1, boneIndex2, boneIndex3, boneIndex4};
	float4x4 boneTrans;
	boneTrans[0] = vec4(1,0,0,0);
	boneTrans[1] = vec4(0,1,0,0);
	boneTrans[2] = vec4(0,0,1,0);
	boneTrans[3] = vec4(0,0,0,1);

	for(int i = 0; i < 5 && weights[i] != 0; i++)
	{
		boneTrans = mul(boneTrans, bones[boneIndexes[i]] * weights[i]);
	}
	float4 alteredPos = mul(float4(IN.pos, 1.0), boneTrans);

	OUT.color = IN.color;
	OUT.pos = mul(alteredPos, mvm);
	OUT.texcoord = IN.texcoord;
}