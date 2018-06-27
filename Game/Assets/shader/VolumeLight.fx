/*!
 * @brief	スプライト用のシェーダー。
 */

struct VSInput{
	float4 pos : SV_Position;
	float2 uv  : TEXCOORD0;
};

struct PSInput{
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D<float4> frontDepthTexture : register(t0);	//カラーテクスチャ。
Texture2D<float4> backDepthTexture : register(t1);	//カラーテクスチャ。
Texture2D<float4> colorTexture : register(t2);	//カラーテクスチャ。
Texture2D<float4> mainDepthTexture : register(t3);	//カラーテクスチャ。
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
	float mainDepth = mainDepthTexture.Sample(Sampler, In.uv).x;
	float frontDepth = frontDepthTexture.Sample(Sampler, In.uv).x;
	float backDepth = backDepthTexture.Sample(Sampler, In.uv).x;
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
	float adjustment = 8000.0f;
	if (frontDepth < mainDepth)
	{
		float depthWidth = mainDepth - frontDepth;
		color *= depthWidth * adjustment;
		color = colorTexture.Sample(Sampler, In.uv);
	}
	return color;
}
