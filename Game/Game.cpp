#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
#include"Player.h"
#include"AI.h"
#include"Stage.h"
#include"Level.h"
#include "AI_manager.h"
#include"AImove.h"
#include"camera.h"
#include"Pasu.h"
#include"keiroK.h"
#include"carRender.h"
#include"tekihei.h"
#include"Geizi.h"
#include"item.h"
#include"car.h"
#include"BGM.h"
Game::Game()
{
	//ここに基本的な発生を描く
	gaizi = NewGO<Geizi>(1, "Geizi");

	player = FindGO<Player>("Player");
	enemy = NewGO<tekihei>(0, "tekihei");
	player->trueGame();

//	pasu2.clear();
	stage = FindGO<Stage>("stage");
	auto car = stage->getcarv();
	for (auto& na : car) {
		na->GetGeizi(gaizi);
	}
	camera1 = NewGO<camera>(0, "camera");
	//enemy= NewGO<tekihei>(0, "enemy");

	/*swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 0, 2);
	m_level[0].Build(moveFilePath);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 1, 1);
	m_level[1].Build(moveFilePath);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 2, 1);
	m_level[2].Build(moveFilePath);*/

	//m_level[1].X = 5.0f;
	//m_level[1].Z=  5.0f;
	//m_level[1].Build(L"lever/leval01.tks");
	//ここに基本的な発生を描く
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	
}
void Game::OnDestroy()
{
	DeleteGO(player);
	//ここで最終的にＤｅｌｅｔｅＧＯを絶対しきる。	
	DeleteGO(FindGO<AI_manager>("AI_manager"));
	DeleteGO(gaizi);
	stage->Car_delete();
	DeleteGO(FindGO<BGM>("BGM"));//BGM
	DeleteGO(camera1);
	DeleteGO(enemy);
	//DeleteGO(FindGO<item>("item"));
	//再起動（タイトル表示）
	NewGO<Taitor>(0, "Taitor");
	stage->Car_create();
	NewGO<Player>(0, "Player");
	NewGO<AI_manager>(0, "AI_manager");
	//enemy = NewGO<tekihei>(0, "enemy");
	NewGO<BGM>(0, "BGM");
}
bool Game::Start()
{
	//カメラを設定。
	m_Fade = FindGO<Fade>("Fade");
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//タイマー
	if (player->getcamera_f() == true)
	{
		timer_s -= 1.0f*GameTime().GetFrameDeltaTime();
		if (timer_s <= 0.0f)
		{
			timer_m--;
			timer_s = 60.0f;
		}
		swprintf_s(test_font, L"%d:%2f", timer_m, timer_s);
	}
	

	//クリア関係？？


	//if(i < loc.GetNumObject()) {
	//	CVector3 pos = loc.GetObjectPosition(i);
	//	//m_point.push_back(m_point);
	//}
	if (m_Fade != NULL&& m_Fade->toumeiodo >= 1.0f) {
		m_Fade->StartFadeIn();
	}


	/*if (Pad(0).IsTrigger(enButtonB) && a >= 2) {
		m_Fade->StartFadeOut();
		a--;

	}
	if (Pad(0).IsTrigger(enButtonA)&&a==1) {
		m_Fade->StartFadeIn();
		a++;
	}
	if (Pad(0).IsTrigger(enButtonLeft)) {
		g += 100.0;
	}
	if (Pad(0).IsTrigger(enButtonRight)) {

		f += 100.0;
	}*/
	/*MainCamera().SetTarget({ 0.0f, 10.0f, 0.5f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();*/
	//i++;
}
void Game::Render(CRenderContext& rc)
{

}
void Game::PostRender(CRenderContext& renderContext)
{
	if (player->getcamera_f() == true)
	{
		m_font.Begin(renderContext);
		m_font.Draw(test_font, font_pos, { 255.0f,255.0f,255.0f,1.0f }, 0.0f, 4.0f, fomt_pivot);
		m_font.End(renderContext);
	}
}