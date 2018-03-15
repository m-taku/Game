#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
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
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.0f });
	MainCamera().SetNear(0.1f);
	MainCamera().SetFar(100.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();
	//ここに基本的な発生を描く
	{
		NewGO<Taitor>(0, "Taitor");

	}

	m_Fade=FindGO<Fade>("Fade");
	m_Fade->StartFadeOut();
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//クリア関係？？
	if (Pad(0).IsTrigger(enButtonB) && a >= 1) {
		m_Fade->StartFadeOut();
		a--;
	}
	if (Pad(0).IsTrigger(enButtonA)&&a==0) {
		m_Fade->StartFadeIn();
		a++;
	}
	
}
void Game::Render(CRenderContext& rc)
{
}