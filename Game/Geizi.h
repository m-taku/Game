#pragma once
class Geizi : public IGameObject
{
public:
	Geizi();
	~Geizi();
	bool Start();
	void Update();

	void Render(CRenderContext& rc);
	CSprite m_sprite;				//スプライト(枠)。
	CShaderResourceView m_texture;	//テクスチャ。
	CVector3 m_position = CVector3::Zero;

	CSprite hm_sprite;				//スプライトh(枠)。

	CVector3 hm_position = CVector3::Zero;

	CSprite n_sprite;				//スプライト（中身）。
	CShaderResourceView n_texture;	//テクスチャ。*/
	CVector3 n_position = CVector3::Zero;

	CSprite hn_sprite;				//スプライトh（中身）。
	CVector3 hn_position = CVector3::Zero;

	float point = 0.0f;
	int  furag = 0;
};

