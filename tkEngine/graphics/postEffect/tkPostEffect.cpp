/*!
 *@brief	ポストエフェクト。
 */

#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkPostEffect.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

namespace tkEngine{
	namespace {
		struct SSimpleVertex {
			CVector4 pos;
			CVector2 tex;
		};
	}
	CPostEffect::CPostEffect()
	{
	}
	CPostEffect::~CPostEffect()
	{
		Release();
	}
	void CPostEffect::Release()
	{
		m_fullscreenQuad.Release();
	}
	void CPostEffect::Create( const SGraphicsConfig& config )
	{
		Release();
		m_fxaa.Init(config);
		m_tonemap.Init(config);
		m_bloom.Init(config);
		m_dithering.Init(config);
		m_monochrome.Init(config);
		InitFullScreenQuadPrimitive();
		InitFinalRenderTarget();
		psShader.Load("shader/VolumeLight.fx", "PSMain", CShader::EnType::PS);
		vsShader.Load("shader/VolumeLight.fx", "VSMain", CShader::EnType::VS);
		struct CB
		{
			CMatrix mat;
			CVector4 color;
		};
		CB cb;
		cb.mat = CMatrix::Identity;
		cb.color = { 1.0f, 1.0f, 1.0f, 1.0f };

		constantBuffer.Create(&cb, sizeof(CB));
	}
	void CPostEffect::Render(CRenderContext& rc)
	{
		//CRenderTarget* targets[] = { &GraphicsEngine().GetMainRenderTarget() };
		//BeginGPUEvent(L"enRenderStep_Render3DModelToScene");
		//rc.OMSetRenderTargets(1, targets);
		//rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);
		//rc.RSSetState(RasterizerState::sceneRender);
		//float blendFactor[4] = { 0.0f };
		//rc.OMSetBlendState(AlphaBlendState::add, 0, 0xFFFFFFFF);

		//rc.RSSetViewport(0.0f, 0.0f, (float)GraphicsEngine().GetFrameBufferWidth(), (float)GraphicsEngine().GetFrameBufferHeight());
		//rc.PSSetShaderResource(3, GraphicsEngine().GetZPrepass().GetDepthTextureSRV());
		//for (int i = 0;i < 3;i++)
		//{
		//	rc.PSSetShaderResource(i, GraphicsEngine().GetVolumeLightTarget()[i].GetRenderTargetSRV());
		//}
		//rc.VSSetShader(vsShader);
		//rc.PSSetShader(psShader);
		//rc.IASetInputLayout(vsShader.GetInputLayout());
		//rc.VSSetConstantBuffer(0, constantBuffer);
		//rc.PSSetConstantBuffer(0, constantBuffer);
		//DrawFullScreenQuad(rc);
		//EndGPUEvent();
		//rc.OMSetBlendState(AlphaBlendState::disable, 0, 0xFFFFFFFF);
		//メインレンダリングターゲットの内容をリゾルブ。
		GraphicsEngine().GetMainRenderTarget().ResovleMSAATexture(rc);
		m_tonemap.Render(rc, this);

		//エフェクトを描画
		GraphicsEngine().GetEffectEngine().Render(rc, this);

		//メインレンダリングターゲットの内容を最終合成用のレンダリングターゲットに描画。
		rc.ResolveSubresource(
			GetFinalRenderTarget().GetRenderTarget(),
			0,
			GraphicsEngine().GetMainRenderTarget().GetRenderTarget(),
			0,
			GetFinalRenderTarget().GetRenderTargetTextureFormat()
		);


		m_bloom.Render(rc, this);
		m_fxaa.Render(rc, this);
		m_dithering.Render(rc, this);
		m_monochrome.Render(rc, this);
		GraphicsEngine().EndPostEffect(rc);
	}
	void CPostEffect::InitFullScreenQuadPrimitive()
	{
		//頂点バッファのソースデータ。
		SSimpleVertex vertices[] =
		{
			{
				CVector4(-1.0f, -1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 1.0f),
			},
			{
				CVector4(1.0f, -1.0f, 0.0f, 1.0f),
				CVector2(1.0f, 1.0f),
			},
			{
				CVector4(-1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(0.0f, 0.0f)
			},
			{
				CVector4(1.0f, 1.0f, 0.0f, 1.0f),
				CVector2(1.0f, 0.0f)
			}

		};
		short indices[] = { 0,1,2,3 };
		
		m_fullscreenQuad.Create(
			D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			4,
			sizeof(SSimpleVertex),
			vertices,
			4,
			CIndexBuffer::enIndexType_16,
			indices
		);
	}
	void CPostEffect::DrawFullScreenQuad(CRenderContext& rc)
	{
		m_fullscreenQuad.Draw(rc);
	}
	void CPostEffect::InitFinalRenderTarget()
	{
		DXGI_SAMPLE_DESC sampleDesc;
		//ポストなのでMSAAはなし。
		ZeroMemory(&sampleDesc, sizeof(sampleDesc));
		sampleDesc.Count = 1;
		sampleDesc.Quality = 0;
		CRenderTarget& mainRt = GraphicsEngine().GetMainRenderTarget();
		m_finalRenderTarget[0].Create(
			mainRt.GetWidth(),
			mainRt.GetHeight(),
			1,
			1,
			mainRt.GetRenderTargetTextureFormat(),
			DXGI_FORMAT_UNKNOWN,
			sampleDesc
		);
		m_finalRenderTarget[1].Create(
			mainRt.GetWidth(),
			mainRt.GetHeight(),
			1,
			1,
			mainRt.GetRenderTargetTextureFormat(),
			DXGI_FORMAT_UNKNOWN,
			sampleDesc
		);
	}
}