#include "stdafx.h"
#include "AI.h"
#include "Player.h"
#define REACH 5.0  //ゾンビの攻撃範囲。この距離まで近づいたら攻撃する。
AI NPC;
//今回はmを引用するNPCのハンドルとして、jを特殊部隊のハンドルとして代用する。これは後に直しておくように。
//NPCとNPCゾンビの両方を処理する。
AI::AI()
{
	pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_speed = 5.0f; //ノーマル状態のときの移動速度。
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
	if (len < REACH) {//攻撃を受ける範囲まで近づいたら確実にダメージを受けるので
		DamageFlag = true;//ダメージフラグをtrueにする。
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
	//一定範囲を徘徊する。

	//一定範囲内に他のNPCを見つけたら
	//float len;
	//if (len) {
	//	if (m->Zonbe == 0) {//それがゾンビではなかったら
	//		//視界内か、角度をとって調べる。

	//		if () {//角度内(視界内)だったら
	//			ZombieChaseNumber = MyNumber; //自分が立っていたパスの番号を記憶する。
	//			pa = Zombie_Chase; //パターンを追跡に変える。
	//		}
	//	}
	//}
}

void AI::NPCZombie_Chase()
{
	//float len = GetKyori(m_position, m->m_position);
	//if (len>80.0f||HitFlag == true) {//他のNPCを見失った(距離が80以上あいた)、あるいは攻撃を与えたら
	//	//元の位置に戻る。

	//	if (ZombieChaseNumber = MyNumber) {//元の位置の番号に戻ったら
	//		pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
	//		HitFlag == false;
	//	}
	//}
	//if (len<REACH) {//NPCに追いついたら
	//	//攻撃する(確実に当たる仕様)。

	//		HitFlag = true; //「NPCに攻撃を当てた」というフラグをたてる。
	//	}
	
}

void AI::NPCZombie_Attack()//vs特殊部隊
{
	//if (BattleFlag == false) {//部隊と戦っておらず、フリーな状態なら
	//	//一番近い部隊に移動する。
	//	float len = GetKyori(m_position,j->m_position );
	//	if (len<REACH) {//部隊に近づいたら
	//		BattleFlag == true;//戦闘を開始する。
	//	}
	//}

	if (BattleFlag == true) {//戦闘状態なら
     	 //部隊に攻撃する。
	}

	//if () {//部隊を倒したら
	//	//「戦闘を終了した」というフラグをたてる。
	//	BattleFlag = false;
	//}
	
}

float AI::GetKyori(CVector3 a, CVector3 b) //2つのオブジェクトの座標を受け取る。
{
	CVector3 v = a - b;
	float len = v.Length();//長さ
	return len;  //2つのオブジェクトの距離を返す。
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

void AI::NPCRuet()//NPCルート
{

}

float AI::VectorAngleDeg(CVector3 c)
{
	float a = 0.0f;
	return a;
}
void AI::Update()
{
	//pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	
	if (ForceFlag==true) {//特殊部隊が出現したら
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
		//NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//他のNPCを見つけた時の処理を書く。
		//NPCZombie_Chase();
		break;
	case Zombie_Attack:
		//NPCZombie_Attack();
		break;
	}

	
	//Muve(m_movespeed);//ムーヴスピード入れると動く
	//m_movespeed.x += 0.001;
	// //qRot回転とキャラの回転を乗算して合成する。
	//qBias.Multiply(m_rotation, qBias);

	//NPCの前方向を計算

	mRot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = mRot.m[2][0];
	m_forward.y = mRot.m[2][1];
	m_forward.z = mRot.m[2][2];
	m_forward.Normalize();
	m_rite.x = mRot.m[0][0];
	m_rite.y = mRot.m[0][1];
	m_rite.z = mRot.m[0][2];
	m_rite.Normalize();
	m_position += m_forward *  m_speed;
	m_position += m_rite * 10 * m_speed;
	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
}
void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
