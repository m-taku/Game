#include "stdafx.h"
#include "Player.h"
#include"Human.h"
#include"taieki.h"
#include"tekihei.h"
#include"Geizi.h"


Player::Player()
{
	hakaba=NewGO<prefab::CEffect>(0);
}


Player::~Player()
{
	DeleteGO(FindGO<taieki>("taieki"));
	
}
bool Player::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);
	m_skinModel.SetShadowCasterFlag(true);
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		30.0,			//半径。 
		100.0f,			//高さ。
		m_position,		//初期位置。
		0
	);
	landpos.x = 2000.0f;
	landpos.z = 0.0f;
	hakaba->Play(L"effect/aura2.efk");
	hakaba->SetPosition(landpos);
	hakaba->SetScale({ 40.0f,40.0f,40.0f });
	return true;
}
void Player::Update()
{
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.x = 0.0f;
	//左スティックの入力量を受け取る。
	float lStick_x = Pad(0).GetLStickXF()*1000.0f;
	float lStick_y = Pad(0).GetLStickYF()*1000.0f;
	//右スティックの入力量を受け取る。
	float rStick_x = Pad(0).GetRStickXF();
	float rStick_y = Pad(0).GetRStickYF();

	
	/*rotX += rStick_y * 5;*/
	rotY = rStick_x * 5;
	/*qBias.SetRotationDeg(CVector3::AxisX, rotX);*/
	qBias1.SetRotationDeg(CVector3::AxisY, rotY);
	m_rotation.Multiply(qBias1);
	if (hakaba != NULL)
	{
		land_to_player = landpos - m_position;
		land_to_player_vector = sqrt(land_to_player.x*land_to_player.x + land_to_player.y*land_to_player.y + land_to_player.z*land_to_player.z);
	}
	

	if (Pad(0).IsTrigger(enButtonA) //Aボタンが押されたら
		&& m_charaCon.IsOnGround()  //かつ、地面に居たら
		) {
		//ジャンプする。
		m_moveSpeed.y = 400.0f;	//上方向に速度を設定して、
		m_charaCon.Jump();		//キャラクターコントローラーにジャンプしたことを通知する。
	}
	m_moveSpeed.y -= 980.0f * GameTime().GetFrameDeltaTime();
	//キャラクターコントローラーを使用して、座標を更新。
	if (m_charaCon.IsOnGround()) {
		//地面についた。
		m_moveSpeed.y = 0.0f;
	}
	if (Pad(0).IsTrigger(enButtonRB2)&& NULL == FindGO<taieki>("taieki"))
	{
		NewGO<taieki>(0,"taieki");
	}
	//プレイヤーの前方向を計算
	
	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_forward.Normalize();
	//右方向
	m_rite.x = mRot.m[0][0];
	m_rite.y = mRot.m[0][1];
	m_rite.z = mRot.m[0][2];
	m_rite.Normalize();
	m_moveSpeed += m_forward*lStick_y;
	m_moveSpeed += m_rite * lStick_x;
	if (hakaba->IsPlay()&&landflag == 1 && land_to_player_vector <= 50.0f)
	{
		m_moveSpeed = CVector3::Zero;
		if (Pad(0).IsTrigger(enButtonA))
		{
			DeleteGO(hakaba);
			FindGO<Geizi>("Geizi")->Satpoint(1.0f);
		}
		if (Pad(0).IsTrigger(enButtonB))
		{
			landflag = 0;
		}
	}
	if (land_to_player_vector > 50.0f)
	{
		landflag = 1;
	}
	m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_moveSpeed);
	m_moveSpeed.z = 0.0f;
	m_moveSpeed.x = 0.0f;
	if (m_position.y <= -100.0f) {
		m_position.y = -100.0f;
	}
	
	m_skinModel.Update(m_position, m_rotation, CVector3::One);
	/*FindGameObjectsWithTag(10, [&](IGameObject* go) {
		CVector3 diff;
		AI* ai = (AI*)go;
		diff = ai->position - m_position;
		if (diff.Length() < 100.0f) {

		}
	});*/
}
void Player::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
