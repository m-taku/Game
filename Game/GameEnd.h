#pragma once
class Fade;
class GameEnd : public IGameObject
{
public:
	GameEnd();
	~GameEnd();
	bool Start();
	void Update();
//	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
private:
	int furgu = 0;
	Fade* fade;
	int taim = 0;
	enum muve
	{
		UP,
		slide,
		idle
	};
	muve flag = UP;
	CSprite syuuryou;				//スプライト(枠)。
	CShaderResourceView you;	//テクスチャ。
	CVector3 m_position;
	CFont m_font;
	CVector2 result_pos = { 0.0f,-800.0f };
	CVector2 result_pivot = { 0.5f,0.5f };
	CVector2 score_pos = { 0.0f,-800.0f };
	CVector2 score_pivot = { 0.5f,0.5f };

	wchar_t inputscore[256];
	wchar_t inputsubscore[256];

};

