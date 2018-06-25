/*!
*@brief	トーンマップ。
*/
#pragma once

namespace tkEngine {
	/*!
	*@brief	モノクロームフィルター
	*/
	class CMonochromeFilter {
	public:
		CMonochromeFilter();
		~CMonochromeFilter();
		/*!
		*@brief	作成。
		*/
		void Init(const SGraphicsConfig& config);

		/*!
		*@brief	モノクロームフィルターのアルファ設定
		*@param[in]	alpha アルファ値(1.0～0.0の間で1.0に近いほどモノクロがかかる
		*/
		void SetAlpha(float alpha)
		{
			m_rate = alpha;
		}

		/*!
		*@brief	モノクロームフィルターの実行。
		*@param[in]	renderContext		レンダリングコンテキスト
		*/
		void Render(CRenderContext& renderContext, CPostEffect* postEffect);

	private:
		float			m_rate;
		CShader			m_vsShader;							//!<頂点シェーダー。
		CShader			m_psShader;							//!<最終合成シェーダー。
		CConstantBuffer	m_cbRate;
		CShaderResourceView m_noiseTexture;
	};
}