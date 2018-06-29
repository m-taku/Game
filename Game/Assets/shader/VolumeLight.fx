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
	float4 color = colorTexture.Sample(Sampler, In.uv);
	float wValue = color.r;
	color.w = 0.0f;
	float adjustment = 0.1f;
	float adjustment2 = 2.0f;
	float scale = 0.0f;
	float powNum = 10.0f;
	if (frontDepth < mainDepth && mainDepth < backDepth)
	{
		float depthWidth = mainDepth - frontDepth;
		scale = pow(min(1.0f, depthWidth * adjustment), powNum) * adjustment2;
		color *= scale;
		color.w = wValue;
	}
	else if(frontDepth < mainDepth)
	{
		float depthWidth = backDepth - frontDepth;
		scale = pow(min(1.0f, depthWidth * adjustment), powNum) * adjustment2;
		color *= scale;
		color.w = wValue;
	}
	return color;
}
