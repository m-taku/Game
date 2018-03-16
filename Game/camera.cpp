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

	//注視点から視点までのベクトルを設定。
	m_toCameraPos.Set(0.0f, 50.0f, 100.0f);
	//プレイヤーのインスタンスを探す。
	m_player = FindGO<Player>("Player");
	if (m_player != NULL)
		target = m_player->m_forward;
		target.z = m_player->m_forward.z - 50.0f;
		Ppos = m_player->m_position;
		Ppos.y += 50.0f;
	//カメラのニアクリップとファークリップを設定する。
	MainCamera().SetTarget(target);
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Ppos);
	MainCamera().Update();

	return true;
}
void camera::Update()
{

}