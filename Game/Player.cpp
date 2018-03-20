#include "stdafx.h"
#include "Player.h"
#include"Human.h"


Player::Player()
{
}


Player::~Player()
{
}
bool Player::Start()
{
	m_position -= {0.0f, 0.0f, 0.0f};
	m_skinModelData.Load(L"modelData/unityChan.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);
	return true;
}
void Player::Update()
{
	m_movespeed = {1.0f, 0.0f, 0.0f};
	CQuaternion qBias;
	qBias = rotation(180);
	Muve(m_movespeed);//ムーヴスピード入れると動く
	m_skinModel.Update(m_position, qBias, { 0.5f,0.5f,0.5f });

}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
