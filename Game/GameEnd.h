#pragma once
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	int furgu = 0,taim=0;

	CSprite GameOuba;				//スプライト(枠)。
	CShaderResourceView Ouba;	//テクスチャ。

	CSprite GameKuria;				//スプライト(枠)。
	CShaderResourceView kuria;	//テクスチャ。
	CVector3 m_position;

};

