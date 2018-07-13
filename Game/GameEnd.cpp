#include "stdafx.h"
#include "GameEnd.h"
#include"Geizi.h"
#include"Player.h"
#include"AI_manager.h"
#include"Game.h"
#include"Fade.h"

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
	inputwstr = L"最終結果";
	int zonbisuu = 0;
	for (int i = 0; i<AI_ado->Getsize(); i++)
	{
		if (AI_ado->RAIseizon[i] == 0)
		{
			zonbisuu++;
		}
	}	for (int i = 0; i<AI_ado->Get2size(); i++)
	{
		if (AI_ado->LAIseizon[i] == 0)
		{
			zonbisuu++;
		}
	}int wariai = 0;
	wariai = zonbisuu / AI_ado->Get_NPC_Number();
	wariai *= 50;
	inputwstr= (L"%d",wariai);
	return true;
}
void GameEnd::Update()
{

	inputwstr;
	font_pos = { 200.0f,200.0f }; 
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

	m_font.Draw(L"最終結果", { 300.0f,0.0f }, { 1.0f,1.0f,1.0f,255.0f }, 0.0f, 1.0f, fomt_pivot);

	m_font.Draw(inputwstr.c_str(), font_pos, { 1.0f,1.0f,1.0f,255.0f }, 0.0f, 1.0f, fomt_pivot);

	m_font.End(rc);
}
