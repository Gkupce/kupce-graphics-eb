//float4 Color	: COLOR0;

struct v2p {
	float4 Position	: POSITION;
	float2 Texcoord	: TEXCOORD0;
};
struct p2f {
	float4 Color	: COLOR;
};
texture ColorTexture : DIFFUSE <
    string ResourceType = "2D";
>;
sampler2D TexSampler = sampler_state {
    Texture = <ColorTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};
void main(v2p IN, out p2f OUT)
{
	OUT.Color = tex2D(TexSampler, IN.Texcoord);
}