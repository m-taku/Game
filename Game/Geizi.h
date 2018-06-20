#pragma once
class tekihei;
class Geizi : public IGameObject
{
public:
	Geizi();
	~Geizi();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void satHP(float a)
	{
		HP -= a;
	}
	void Satpoint(float a)
	{
		point += a;
	}
	float GatHP() 
	{
		return HP;
	}
	float GatFragu()
	{
		return furag;
	}
	void SatFragu()
	{
		furag++;
	}
	int GatHPfurag()
	{
		return HPfurag;
	}

	float Get_keifou_saiz()
	{
		return keifou_saiz;//これが0.95以上になると敵兵が出てくる。
	}
private:
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
	tekihei* haus;
	CSprite hy_sprite;				//スプライト(枠)。
	CShaderResourceView hy_texture;	//テクスチャ。
	float point = 0.0f;
	float HP = 0.95f;
	float  furag = 0.0f; //特殊部隊が出たら1になる。
	int HPfurag = 0;
	float keifou_saiz = 0.0f, HP_saiz = 0.95f;
	float kasoku = 0;
};

