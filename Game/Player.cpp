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
	CQuaternion qBias;
	qBias = rotation(0);
	//プレイヤーの前方向を計算
	CMatrix mRot;
	mRot.MakeRotationFromQuaternion(qBias);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_skinModel.Update(m_position, qBias, { 0.5f,0.5f,0.5f });
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
