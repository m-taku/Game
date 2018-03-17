#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

bool camera::Start()
{

	
	

	return true;
}
void camera::Update()
{
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("Player");
	if (m_player != NULL){
		target = m_player->m_position + m_player->m_forward * 50.0f;
		target.y = m_player->m_position.y + 50.0f;
		/*target.z = m_player->m_position.z + m_player->m_forward.z + 50.0f;
		target.y = m_player->m_position.y + m_player->m_forward.y + 50.0f;*/
		Ppos = m_player->m_position;
		Ppos.y = m_player->m_position.y + 50.0f;
	}
		
	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetTarget(target);
	MainCamera().SetNear(20.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Ppos);
	MainCamera().Update();
}