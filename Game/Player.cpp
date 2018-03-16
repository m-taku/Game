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
	//左スティックの入力量を受け取る。
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();
	m_position.x += 5 * lStick_x;
	m_position.z += 5 * lStick_y;
	rotY += rStick_x * 5;
	qBias = rotation(rotY);
	//プレイヤーの前方向を計算
	
	mRot.MakeRotationFromQuaternion(qBias);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_forward.Normalize();
	m_skinModel.Update(m_position, qBias, { 1.0f, 1.0f,1.0f });
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
