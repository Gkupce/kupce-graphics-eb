struct v2p {
	float4 Position	: POSITION;
	float4 Color	: COLOR0;
	float2 Texcoord	: TEXCOORD0;
};
struct p2f {
	float4 Color	: COLOR0;
};

sampler2D tex0;

void main(in v2p IN, out p2f OUT) 
{
	OUT.Color = mul(IN.Color, tex2D(tex0, IN.Texcoord));
}