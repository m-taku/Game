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
Texture2D<float4> noiseTexture : register(t1);	//ノイズテクスチャ。
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
	float blendRate = 0.1f;
	float4 noiseColor = noiseTexture.Sample(Sampler, In.uv);
	srcColor = srcColor * (1.0f - blendRate) + noiseColor * blendRate;
	float4 color = dstColor * clamp((1.0f - rate), 0.0f, 1.0f) + srcColor * clamp(rate, 0.0f, 1.0f);
	color.w = 1.0f;
	return  color;
}
