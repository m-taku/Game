#include "tkEngine/tkEnginePreCompile.h"
#include "tkEngine/graphics/postEffect/tkMonochromeFilter.h"
#include "tkEngine/graphics/tkPresetRenderState.h"

namespace tkEngine {
	CMonochromeFilter::CMonochromeFilter()
	{
	}
	CMonochromeFilter::~CMonochromeFilter()
	{
	}
	void CMonochromeFilter::Init(const SGraphicsConfig& config)
	{
		m_rate = 0.0f;
		m_cbRate.Create(&m_rate, sizeof(float));
		m_psShader.Load("shader/monochrome.fx", "PSMain", CShader::EnType::PS);
		m_vsShader.Load("shader/monochrome.fx", "VSMain", CShader::EnType::VS);
		m_noiseTexture.CreateFromDDSTextureFromFile(L"sprite/noise.dds");
	}
	void CMonochromeFilter::Render(CRenderContext& rc, CPostEffect* postEffect)
	{
		//if (!m_isEnable) {
		//	return;
		//}
		CGraphicsEngine& ge = Engine().GetGraphicsEngine();
		ge.BeginGPUEvent(L"CMonochromeFilter::Render");
		CRenderTarget& sceneSRV = postEffect->GetFinalRenderTarget();
		postEffect->ToggleFinalRenderTarget();
		CRenderTarget& rt = postEffect->GetFinalRenderTarget();
		CRenderTarget* rts[] = {
			&rt
		};
		rc.UpdateSubresource(m_cbRate, &m_rate);
		rc.RSSetViewport(0.0f, 0.0f, rt.GetWidth(), rt.GetHeight());
		rc.OMSetRenderTargets(1, rts);
		rc.OMSetBlendState(AlphaBlendState::disable, 0, 0xFFFFFFFF);
		rc.OMSetDepthStencilState(DepthStencilState::disable, 0);
		rc.PSSetShaderResource(0, sceneSRV.GetRenderTargetSRV());
		rc.PSSetShaderResource(1, m_noiseTexture);
		rc.PSSetConstantBuffer(0, m_cbRate);
		rc.VSSetShader(m_vsShader);
		rc.PSSetShader(m_psShader);
		postEffect->DrawFullScreenQuad(rc);

		//ñﬂÇ∑ÅB
		rc.OMSetDepthStencilState(DepthStencilState::SceneRender, 0);

		rc.PSUnsetShaderResource(0);
		ge.EndGPUEvent();
	}
}