#include "stdafx.h"
#include "Game.h"
#include"Fade.h"
#include"Taitor.h"
#include"Player.h"
#include"AI.h"
#include"Stage.h"
#include"Level.h"
#include"AImove.h"
#include"camera.h"
#include"Pasu.h"
#include"keiroK.h"
#include"tekihei.h"
#include"Geizi.h"
Game::Game()
{
	NewGO<Geizi>(0, "Geizi");
	NewGO<Player>(0, "Player");
	for (int k = 0; k < 2; k++) {
		siminUI.push_back(NewGO<AImove>(0, "AIm"));
		simin.push_back(NewGO<AI>(0, "AI"));

	}
	NewGO<Stage>(0, "stage");
	NewGO<camera>(0, "camera");/*

	m_level[0].Build(L"lever/leval001.tks");*/
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"lever/leval00%d.tks", 1);
	pasu.Load(moveFilePath);
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

	//ここで最終的にＤｅｌｅｔｅＧＯを絶対しきる。




	//再起動（タイトル表示）

	NewGO<Taitor>(0, "Taitor");
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
		
	}
	m_Fade=FindGO<Fade>("Fade");

	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");
	m_skinModelRender->SetScale({ 0.1f, 0.1f, 0.1f } );*/
	return true;
}
void Game::Update()
{
	//クリア関係？？
		if (m_Fade != NULL) {
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
	}
	MainCamera().SetTarget({ 0.0f, 10.0f, 0.5f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition({ 30.0f, 10.0f, 0.0f });
	MainCamera().Update();*/
}
void Game::Render(CRenderContext& rc)
{

}