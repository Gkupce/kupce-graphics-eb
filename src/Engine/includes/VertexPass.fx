struct a2v{
	float4 pos : POSITION;
	float4 color : COLOR0;
	float2 texcoord : TEXCOORD0;
};

struct v2p {
	float4 pos : POSITION;
	float4 color : COLOR0;
	float2 texcoord : TEXCOORD0;
};

float4x4 mvm : WorldViewProjection;
void mainVS(a2v IN, out v2p OUT)
{
	//v2p OUT;
	float alteration = cos(IN.pos.y);
	alteration = alteration * alteration * 0.8;
	float4 alteredPos = float4(IN.pos.xyz * alteration, IN.pos.w);
	
	OUT.color = IN.color;
	OUT.pos = mul(alteredPos, mvm);
	OUT.texcoord = IN.texcoord;
}