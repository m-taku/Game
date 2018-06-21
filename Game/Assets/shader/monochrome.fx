/*!
 * @brief	スプライト用のシェーダー。
 */
cbuffer PSCb : register(b0) {
	float rate;
};
struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);	//カラーテクスチャ。
sampler Sampler : register(s0);

PSInput VSMain(VSInput In) 
{
	PSInput psIn;
	psIn.pos = In.pos;
	psIn.uv = In.uv;
	return psIn;
}
float4 PSMain( PSInput In ) : SV_Target0
{
	float4 srcColor = colorTexture.Sample(Sampler, In.uv);
	float4 dstColor = srcColor;
	float len = srcColor.x * 0.299 + srcColor.y * 0.587 + srcColor.z * 0.114;
	srcColor.x = len;
	srcColor.y = len;
	srcColor.z = len;
	float4 color = dstColor * (1.0f - rate) + srcColor * rate;
	return  color;
}
