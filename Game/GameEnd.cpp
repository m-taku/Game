#include "stdafx.h"
#include "GameEnd.h"
#include"Geizi.h"
#include"Player.h"
#include"AI_manager.h"
#include"Game.h"
#include"Fade.h"
#include"tekihei.h"

GameEnd::GameEnd()
{
}


GameEnd::~GameEnd()
{
}
bool GameEnd::Start()
{

	fade = FindGO<Fade>("Fade");
	Geizi* hama= FindGO<Geizi>("Geizi");
	Player* player = FindGO<Player>("Player");
	tekihei* Tekhei = FindGO<tekihei>("tekihei");
	if (hama->GatHPfurag() >= 1) {
		furgu++;
	}
	m_position = { 0.0,300.0,0.0 };
	switch (furgu)
	{
	case 0://プレイヤーの勝ち
		you.CreateFromDDSTextureFromFile(L"sprite/GameClear.dds");//ここに勝利時のリザルト画面を表示
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
		break;
	case 1://プレイヤーの負け
		player->falseGame();
		you.CreateFromDDSTextureFromFile(L"sprite/GameOver.dds");//ここに敗北時のリザルト画面を表示
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
		break;
	default:
		break;
	}

	int isa = AI_ado->Get_NPC_Number();
	int zonbisuu = 0;
	for (int i = 0; i<AI_ado->Getsize(); i++)
	{
		if (AI_ado->RAIseizon[i] <= 0)
		{
			zonbisuu++;
		}
	}	for (int i = 0; i<AI_ado->Get2size(); i++)
	{
		if (AI_ado->LAIseizon[i] <= 0)
		{
			zonbisuu++;
		}
	}float wariai = 0.00f;
	wariai = ((float)zonbisuu / (float)AI_ado->Get_NPC_Number())*50;
	wariai +=((float)Tekhei->soma / (float)teki)*50;
	swprintf_s( inputscore, L"得点：%d点", (int)wariai);
	return true;
}
void GameEnd::Update()
{
	switch (flag)
	{
	case UP:
		result_pos.y += 30.0f;
		if (result_pos.y >= 300.0f)
		{
			result_pos.y = 300.0f;
			flag = slide;
		}
		break;
	case slide:
		score_pos.y += 30.0f;
		if (score_pos.y >= 100.0f)
		{
			score_pos.y = 100.0f;
			flag = idle;
		}
		break;
	case idle:
		if (Pad(0).IsTrigger(enButtonA))
		{
			DeleteGO(FindGO<Game>("Game"));
			DeleteGO(this);
		}
		break;
	default:
		break;
	}
	//if (taim <= 300) {
	//	m_position.y -= 1.0;
	//	syuuryou.Update(m_position, CQuaternion::Identity, { 10.0f,10.0f,10.0f });
	//	taim++;
	//}
	//else {
	//	fade->StartFadeOut();
	//	if (fade->toumeiodo >= 1.0f) {
	//		DeleteGO(FindGO<Game>("Game"));
	//		DeleteGO(this);
	//	}
	//}
}

void GameEnd::PostRender(CRenderContext& rc)
{
	//syuuryou.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	m_font.Begin(rc);

	m_font.Draw(L"最終結果", result_pos, { 0.0f,0.0f,0.0f,255.0f }, 0.0f, 3.0f, result_pivot);

	m_font.Draw(inputscore, score_pos, { 1.0f,1.0f,1.0f,255.0f }, 0.0f,5.0f, score_pivot);

	m_font.End(rc);
}
