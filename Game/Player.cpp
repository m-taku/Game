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
<<<<<<< HEAD
	m_movespeed = {1.0f, 0.0f, 0.0f};
	CQuaternion qBias;
	qBias = rotation(180);
	Muve(m_movespeed);//ムーヴスピード入れると動く
	m_skinModel.Update(m_position, qBias, { 0.5f,0.5f,0.5f });

=======
	//左スティックの入力量を受け取る。
	float lStick_x = Pad(0).GetLStickXF();
	float lStick_y = Pad(0).GetLStickYF();
	//右スティックの入力量を受け取る。
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();
	
	/*rotX += rStick_y * 5;*/
	rotY = rStick_x * 5;
	/*qBias.SetRotationDeg(CVector3::AxisX, rotX);*/
	qBias1.SetRotationDeg(CVector3::AxisY, rotY);
	m_rotation.Multiply(qBias1);
	//プレイヤーの前方向を計算
	
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_forward.Normalize();
	m_rite.x = mRot.m[0][0];
	m_rite.y = mRot.m[0][1];
	m_rite.z = mRot.m[0][2];
	m_rite.Normalize();
	m_position += m_forward * 10 * lStick_y;
	m_position += m_rite * 10 * lStick_x;
	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
>>>>>>> 2d17ab8e8be7b1d97574d3fd2aba03b4fc0ce85e
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
