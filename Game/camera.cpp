#include "stdafx.h"
#include "camera.h"
#define tall 10.0f


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
		
		position_of_player = m_player->Getbonepos();
		target = position_of_player + m_player->GetFoeward() * 100.0f;
		target.y = position_of_player.y + tall;
		
		d += rStick_y*5.0f;
		d = max(d, -50.0f);
		d = min(d, 50.0f);
		target.y = target.y + d;
		/*target.z = m_player->m_position.z + m_player->m_forward.z + 50.0f;
		target.y = m_player->m_position.y + m_player->m_forward.y + 50.0f;*/
		Ppos = m_player->Getbonepos() + m_player->GetFoeward() * 10.0f;
		Ppos.y = position_of_player.y + tall;
		/*if (m_player->GetPosition().z <= 0.0f)
		{
			
		}*/
	}
	Ppos.z += 500.0f;
	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetTarget(target);
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Ppos);
	MainCamera().Update();
}