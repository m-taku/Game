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
Game::Game()
{
	//ここに基本的な発生を描く
	gaizi = NewGO<Geizi>(1, "Geizi");

	player = NewGO<Player>(0, "Player");

	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"lever/levalAI%d%d.tks", 0, 2);
	pasu[0].Load(moveFilePath,No);
	No = 1;
	swprintf_s(moveFilePath, L"lever/levalAI%d%d.tks", 2, 2);
	pasu[1].Load(moveFilePath,No);
	No = 0;
#ifndef Mizuki_baka
	carRender* kar = NewGO<carRender>(0, nullptr);
#endif // Mizuki_baka
	da.push_back(AIR1);
	da.push_back(AIR2);
	da.push_back(AIR3);
	da.push_back(AIR4);
	da.push_back(AIR5);
	da.push_back(AIR6);
	da.push_back(AIR7);
	da.push_back(AIR8);
	da.push_back(AIR9);
	da.push_back(AIR10);
	da.push_back(AIR11);
	da.push_back(AIR12);
	da.push_back(AIR13);
	da.push_back(AIR14);
	da.push_back(AIR15);
	da.push_back(AIR16);
	da.push_back(AIR17);
	da.push_back(AIR18);
	da.push_back(AIR19);
	da.push_back(AIR20);
	da.push_back(AIR21);
	da.push_back(AIR22);
	da.push_back(AIR23);
	da.push_back(AIR24);
	da.push_back(AIR25);
	da.push_back(AIR26);
	for (int k = 0; k < da.size(); k++) {
		AI* AIR = NewGO<AI>(0, "AI");
		AIR->GetGame(this);
		Rsimin.push_back(AIR);
		RAIseizon.push_back(1);
	}
	No = 0;
	Leftfrag = 1;
	da2.push_back(AIL1);
	da2.push_back(AIL2);
	da2.push_back(AIL3);
	da2.push_back(AIL4);
	da2.push_back(AIL5);
	da2.push_back(AIL6);
	da2.push_back(AIL7);
	da2.push_back(AIL8);
	da2.push_back(AIL9);
	da2.push_back(AIL10);
	da2.push_back(AIL11);
	da2.push_back(AIL12);
	da2.push_back(AIL13);
	da2.push_back(AIL14);
	da2.push_back(AIL15);
	da2.push_back(AIL16);
	da2.push_back(AIL17);
	da2.push_back(AIL18);
	da2.push_back(AIL19);
	da2.push_back(AIL20);
	da2.push_back(AIL21);
	da2.push_back(AIL22);
	da2.push_back(AIL23);
	da2.push_back(AIL24);
	da2.push_back(AIL25);
	da2.push_back(AIL26);
	da2.push_back(AIL27);
	da2.push_back(AIL28);
	da2.push_back(AIL29);
	da2.push_back(AIL30);
	da2.push_back(AIL31);
	da2.push_back(AIL32);
	da2.push_back(AIL33);
	da2.push_back(AIL34);
	da2.push_back(AIL35);
	da2.push_back(AIL36);
	da2.push_back(AIL37);
	da2.push_back(AIL38);
	da2.push_back(AIL39);
	da2.push_back(AIL40);
	da2.push_back(AIL41);
	da2.push_back(AIL42);
	da2.push_back(AIL43);
	for (int k = 0; k < da2.size(); k++) {
		AI* AIL = NewGO<AI>(0, "AI");
		AIL->GetGame(this);
		Lsimin.push_back(AIL);
		LAIseizon.push_back(1);
	}
	No = 0;
	//carを増やした時のの変更点
	pasu2.push_back(movepasu1);
	pasu2.push_back(movepasu2);
	//pasu2.push_back(movepasu3);
	//pasu2.push_back(movepasu4);
	//pasu2.push_back(movepasu5);
	//pasu2.push_back(movepasu6);
	//pasu2.push_back(movepasu7);
	//pasu2.push_back(movepasu8);
	//pasu2.push_back(movepasu9);
	//pasu2.push_back(movepasu10);
	//pasu2.push_back(movepasu11);
	//pasu2.push_back(movepasu12);
	//pasu2.push_back(movepasu13);
	//pasu2.push_back(movepasu14);
	//pasu2.push_back(movepasu15);
	//pasu2.push_back(movepasu16);
	//pasu2.push_back(movepasu17);
	//pasu2.push_back(movepasu18);
	//pasu2.push_back(movepasu19);
	//pasu2.push_back(movepasu20);
	//pasu2.push_back(movepasu21);
	//pasu2.push_back(movepasu22);
	//pasu2.push_back(movepasu23);

#ifndef Mizuki_baka
	kar->Satcarkosuu(pasu2.size());
#endif // Mizuki_baka
	for (int i = 0; i < pasu2.size(); i++) {
		carv.push_back(NewGO<car>(0, "car"));

#ifndef Mizuki_baka
		carv[i]->gatcarRender(*kar);
#endif // Mizuki_baka
	}

	player->SetGame();

//	pasu2.clear();
	Car = FindGO<car>("car");
	Car->GetGeizi(gaizi);
	camera1 = NewGO<camera>(0, "camera");

	/*swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 0, 2);
	m_level[0].Build(moveFilePath);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 1, 1);
	m_level[1].Build(moveFilePath);
	swprintf_s(moveFilePath, L"lever/matilevel%d0%d.tks", 2, 1);
	m_level[2].Build(moveFilePath);*/

	CLocData loc;
	loc.Load(L"lever/laitLv001.tks");
	for (int i = 0; i < loc.GetNumObject(); i++) {
		point.push_back(NewGO<prefab::CPointLight>(0));
		CVector3 f= loc.GetObjectPosition(i);
		f.y = 500.0f;
		point[i]->SetPosition(f);
		point[i]->SetColor({ 255.0f,255.0f, 0.0f,0.0f });
		point[i]->SetAttn({ 700.0f,4.0f ,0.0f });	 
	}
	m_sunLig = NewGO<prefab::CDirectionLight>(0);
	CVector3 lightDir = { 0.707f, -0.707f, 0.0f };
	m_sunLig->SetDirection(lightDir);
	m_sunLig->SetColor({ 1.0f, 1.0f, 3.0f, 1.0f });
	LightManager().SetAmbientLight({1.0f, 1.0f, 1.0f });
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
	DeleteGO(FindGO<AI_manager>("AI_manager"));
	DeleteGO(gaizi);
	DeleteGO(Car);
	DeleteGO(camera1);
	DeleteGO(FindGO<item>("item"));
	//再起動（タイトル表示）
	NewGO<Taitor>(0, "Taitor");
	NewGO<Player>(0, "Player");
	NewGO<AI_manager>(0, "AI_manager");
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