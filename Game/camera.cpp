#include "stdafx.h"
#include "camera.h"
#define tall 0.0f


camera::camera()
{
}


camera::~camera()
{
}

bool camera::Start()
{
	
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("Player");
	return true;
}
void camera::Update()
{
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();
	
	if (m_player != NULL){
		Pboneforward = m_player->Getboneforward();
		cameradeg += rStick_y*(-3.0f);//こ↑こ↓を変えることでカメラ操作の上下を変えられる。
		Crot.SetRotationDeg(m_player->Getboneright(), cameradeg);
		Crot.Multiply(Pboneforward);
		position_of_player = m_player->Getbonepos();
		target = position_of_player+Pboneforward*100.0f;
		cameradeg = max(cameradeg, -60.0f);
		cameradeg = min(cameradeg, 35.0f);
		
		//target = position_of_player + m_player->Getboneforward() * 100.0f;
		//target.y = position_of_player.y + tall;
		//d += rStick_y*5.0f;
		//target += m_player->Getboneup()*d;
		


	/*	d = max(d, -50.0f);
		d = min(d, 50.0f);*/
		/*Ppos = m_player->Getbonepos() + m_player->Getboneforward() * 10.0f;
		Ppos.y = position_of_player.y + tall;*/
		/*if (m_player->GetPosition().z <= 0.0f)
		{
			
		}*/
	}
	Ppos = position_of_player + m_player->Getboneforward()*17.0f;
	//Ppos.z -= 300.0f;
	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetTarget(target);
	MainCamera().SetNear(1.0f);
	MainCamera().SetUp(m_player->Getboneup());
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Ppos);
	MainCamera().Update();
	GraphicsEngine().GetMonochrome();
}