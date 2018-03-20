#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
#include"Player.h"
#include"AI.h"
#include"Stage.h"
<<<<<<< HEAD
#include"Level.h"
#include"AImove.h"
=======
#include"camera.h"
>>>>>>> 2d17ab8e8be7b1d97574d3fd2aba03b4fc0ce85e
Game::Game()
{
	//ここに基本的な発生を描く
	NewGO<Taitor>(0,"Taitor");
}


Game::~Game()
{
}
void Game::InitSceneLight()
{
	
}
void Game::OnDestroy()
{
	//ここで最終的にＤｅｌｅｔｅＧＯを絶対しきる。




	//再起動（タイトル表示）
	NewGO<Game>(0, nullptr);
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.5f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();
	//ここに基本的な発生を描く
	{
		NewGO<Taitor>(0, "Taitor");
		NewGO<Player>(0, "Player");
		//NewGO<AI>(0, "AI");
		NewGO<Stage>(0, "stage");
<<<<<<< HEAD
		m_level.Build(L"lever/leval01.tks");
		NewGO<AImove>(0, "na");
=======
		NewGO<camera>(0, "camera");
>>>>>>> 2d17ab8e8be7b1d97574d3fd2aba03b4fc0ce85e
	}

	m_Fade=FindGO<Fade>("Fade");
	if (m_Fade != NULL) {
		m_Fade->StartFadeOut();
		a++;
	}
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//クリア関係？？
	
	if (Pad(0).IsTrigger(enButtonB) && a >= 2) {
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
	}
}
void Game::Render(CRenderContext& rc)
{
}