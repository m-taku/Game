#pragma once
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
private:
	int furgu = 0;
	int taim = 0;
	CSprite syuuryou;				//スプライト(枠)。
	CShaderResourceView you;	//テクスチャ。
	CVector3 m_position;
};

