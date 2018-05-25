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
#include"item.h"
#include"Osu.h"
#include"Mes.h"
#include"Dog.h"
#include"car.h"
#include "tkEngine\light\tkDirectionLight.h"
#include"tkEngine/graphics/tkLight.h"
#include "tkEngine\light\tkPointLight.h"

Game::Game()
{
	gaizi = NewGO<Geizi>(1, "Geizi");
	player = NewGO<Player>(0, "Player");

	for (int k = 0; k < 4; k++) {
		simin.push_back(NewGO<AI>(0, "AI"));
	}
	No = 0;
	//carを増やした時のの変更点
	pasu2.push_back(movepasu1);
	pasu2.push_back(movepasu2);
	pasu2.push_back(movepasu3);
	pasu2.push_back(movepasu4);
	pasu2.push_back(movepasu5);
	pasu2.push_back(movepasu6);
	pasu2.push_back(movepasu7);
	pasu2.push_back(movepasu8);
	for (int i = 0; i <8 ; i++) {
		carv.push_back(NewGO<car>(0, "car"));
	}
	stge = NewGO<Stage>(0, "stage");
	camera1 = NewGO<camera>(0, "camera");


	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"lever/levalAI0%d.tks", 2);
	pasu.Load(moveFilePath);
	//swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 0, 1);
	//m_level[0].Build(moveFilePath);
	//swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 1, 1);
	//m_level[1].Build(moveFilePath);
	//swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 2, 1);
	//m_level[2].Build(moveFilePath);
	CLocData loc;
	loc.Load(L"lever/laitLv001.tks");
	for (int i = 0; i < loc.GetNumObject(); i++) {
		prefab::CPointLight* point = NewGO<prefab::CPointLight>(0);
		CVector3 f= loc.GetObjectPosition(i);
		f.y = 500.0f;
		point->SetPosition(f);
		point->SetColor({ 255.0f,255.0f, 0.0f,0.0f });
		point->SetAttn({ 700.0f,4.0f ,0.0f });
		 
	}
	m_sunLig = NewGO<prefab::CDirectionLight>(0);
	CVector3 lightDir = { 0.707f, -0.707f, 0.0f };
	m_sunLig->SetDirection(lightDir);
	m_sunLig->SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	LightManager().SetAmbientLight({ 1.0f, 1.0f, 1.0f });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);
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
	for (int k = 0; k < 4; k++) {
		DeleteGO(simin[k]);
	}
	for (int i = 0; i < 2; i++) {
		DeleteGO(carv[i]);
	}
	DeleteGO(gaizi);
	DeleteGO(stge);
	DeleteGO(camera1);
	DeleteGO(FindGO<item>("item"));

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