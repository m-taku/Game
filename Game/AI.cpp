#include "stdafx.h"
#include "AI.h"
#include "Player.h"

AI NPC;
//今回はmを引用するNPCのハンドルとして代用する。これは後に直しておくように。
//NPCとNPCゾンビの両方を処理する。
AI::AI()
{
	pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_movespeed = { 0.0f, 0.0f, -0.1f }; //ノーマル状態のときの移動速度。
}


AI::~AI()
{
}
bool AI::Start()
{
	m_position -= {30.0f,10.0f, 0.0f};
	m_skinModelData.Load(L"modelData/unityChan.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);

	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();

	return true;
}

void AI::NPCNormal()
{
	Player* pl=FindGO<Player>("Player");
	CVector3 v = m_position - pl->m_position;
	float len = v.Length();//長さ
	if (len<50.0f) {//プレイヤーを見つけたら
		v.Normalize();//正規化して向きベクトルにする。
		//プレイヤーから逃げる。
	}
	if (DamageFlag == true) {//プレイヤーからの攻撃を受けたら
		static int i = 0; //30フレームをカウントする。
		if (i >= 30) {
			pa = Damage;//30フレーム経過したらパターンをダメージに変える。
		}
		else {
			i++; //1フレーム経過をカウントする。
		}
		
	}
}

void AI::NPCDamage()
{
	pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
	m_movespeed = { 0.5f, 0.0f, 0.0f }; //ゾンビノーマル状態のときの移動速度に変える。
	Zonbe = 1;
}

void AI::NPCZombie_Normal()
{
	if () {//他のNPCを見つけたら
		if (m->Zonbe == 0) {//それがゾンビではなかったら
			pa = Zombie_Chase; //パターンを追跡に変える。
		}
	}
}

void AI::NPCZombie_Chase()
{
	if () {//他のNPCを見失ったら
		//元の位置に戻す。

		if () {//元の位置に戻ったら
			pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
		}
	}
	if () {//NPCに追いついたら
		//攻撃する。

		if (m->DamageFlag == true) {//感染させたら
			HitFlag = true; //「NPCに攻撃を当てた」というフラグをたてる。
		}
		
	}
	if (HitFlag == true) {//攻撃を当てたたら
		if () {//元の位置に戻してから
			pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
			HitFlag == false;
		}
	}
}

void AI::NPCZombie_Attack()//vs特殊部隊
{
	if () {//部隊に近づいたら
		HitFlag = true; //部隊に攻撃する。
	}
}

void AI::Turn()//ここ
{
	if (fabsf(m_movespeed.x) < 0.001f
		&& fabsf(m_movespeed.z) < 0.001f) {
		//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
		//このフレームではキャラは移動していないので旋回する必要はない。
		return;
	}
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる関数。
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//これが回転角度になる。
	float angle = atan2(m_movespeed.x, m_movespeed.z);
	//atanが返してくる角度はラジアン単位なので
	//SetRotationDegではなくSetRotationを使用する。
	m_rotation.SetRotation(CVector3::AxisY, angle);
}

void AI::NPCRuet()
{

}
void AI::Update()
{
	//pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	
	if () {//特殊部隊が来たら
		pa = Zombie_Attack; //パターンをゾンビアタックに切り替える。
	}
	CQuaternion qBias;
	qBias = rotation(270);
	switch (pa) {
	case Normal:
		//NPCの動きを書く。
		NPCNormal();
		break;
	case Damage:
		NPCDamage();
		break;
	case Zombie_Normal:
		NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//他のNPCを見つけた時の処理を書く。
		NPCZombie_Chase();
		break;
	case Zombie_Attack:
		NPCZombie_Attack();
		break;
	}
	Turn();
	Muve(m_movespeed);//ムーヴスピード入れると動く
	m_movespeed.x += 0.001;
	 //qRot回転とキャラの回転を乗算して合成する。
	qBias.Multiply(m_rotation, qBias);
	m_skinModel.Update(m_position, qBias, { 0.5f,0.5f,0.5f });
}
void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
