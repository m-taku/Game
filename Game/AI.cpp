#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"tekihei.h"
#define REACH 100.0  //ゾンビの攻撃範囲。この距離まで近づいたら攻撃する。
#define PI 3.141592653589793 
//AI NPC;
//今回はmを引用するNPCのハンドルとして、jを特殊部隊のハンドルとして代用する。これは後に直しておくように。
//NPCとNPCゾンビの両方を処理する。
AI::AI()
{
	pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_speed = 500.0f; //ノーマル状態のときの移動速度。
}
AI::~AI()
{
	//m_charaCon.RemoveRigidBoby();
}
bool AI::Start()
{
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	game=FindGO<Game>("Game");
	iNo = game->No++;
	m_position= game->pasu.m_pointList[game->da[iNo][0] - 1];
	m_position.y = 0.0f;
	//キャラのスキンモデルのロードは各自サブクラスで行う。
	m_skinModelData.Load(L"modelData/unityChan.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);

	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	A_charaCon.Init(
		50.0,			//半径。 
		100.0f,			//高さ。
		m_position,		//初期位置。
		1
	);
	game->siminUI[iNo]->kyorikeisan(game->da[iNo][1] - 1);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	m_rotation.SetRotationDeg(CVector3::AxisY,VectorAngleDeg(game->siminUI[iNo]->bekutor));
	SetTags(10);
	m_skinModel.SetShadowCasterFlag(true);
	return true;
}
void AI::NPCNormal()
{
	CVector3 v = game->siminUI[iNo]->K - m_position; //Kが次の目的地
	float len = v.Length();//長さ
	if (30 <= len) {
		float angle = VectorAngleDeg(v);
		if (angle>=3.0) {
			v.y = 0.0f;
			v.Normalize();
			CVector3 forward = this->m_forward;
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(forward, v);
			rotAxis.Normalize();
			CQuaternion qBias1;
			qBias1.SetRotationDeg(rotAxis, 3.0f);
			m_rotation.Multiply(qBias1);
		}
		else {
			//if (angle >= 2.0f) {
			//	v.y = 0.0f;
			//	v.Normalize();
			//	CVector3 forward = this->m_forward;
			//	//回転軸を求める。
			//	CVector3 rotAxis;
			//	rotAxis.Cross(forward, v);
			//	rotAxis.Normalize();
			//	CQuaternion qBias1;
			//	qBias1.SetRotationDeg(rotAxis, angle);
			//	m_rotation.Multiply(qBias1);
			//}
			//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);
		}
	}
	else {
		if (ima >= 6)//今のポジションが6なら
			//0にリセットする。0,1,2,3,4,5の順番。
			ima = 0;
		game->siminUI[iNo]->kyorikeisan(game->da[iNo][ima++] - 1);
	}
	//FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//	if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
	//		AI* ai = (AI*)go;
	//		if (ai->Zonbe == 0) {  //それがゾンビでなかったら
	//			CVector3 kyori1 =   ai->m_position - this->m_position;//自分との距離を求める。
	//			float f = kyori1.Length();
	//			if (Siya(kyori1, f)) { //距離が攻撃範囲以内だったら

	//				CQuaternion qBias1;
	//				qBias1.SetRotationDeg(CVector3::AxisY, 3.0f);
	//				m_rotation.Multiply(qBias1);

	//			}
	//		}
	//	}

	//});
	//if (len1 < 500.0f) {//プレイヤーを見つけたら
	//	if (fabsf(VectorAngleDeg(v2)) <= 45.0f) {
	//		Gaizi->point += 0.1f;
	//		pa = Escape;
	//		retu_position = m_position;
	//		m_speed = 3000.0f;
	//		//DamageFlag = true;
	//		//プレイヤーから逃げる。
	//	}
	//}
	//	/////////////////////////////////
	//	//一定のルートをうろうろする処理。
	//	/////////////////////////////////
	//
	//	FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
	//			AI* ai = (AI*)go;
	//			if (ai->Zonbe == 1) {                                        //それがゾンビだったら
	//				float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
	//				if (kyori < 60.0f) {                                     //距離が視界範囲以内だったら
	//					float angle = VectorAngleDeg(ai->m_position);        //検索対象の座標を引数にする。
	//					if (angle <= 45.0f&&angle >= -45.0f) {                //角度が視界内だったら
	//																		  //ゾンビから逃げる。
	//						muki.x = m_forward.x*(-1);
	//						muki.y = m_forward.y*(-1);
	//						muki.z = m_forward.z*(-1);//反対の向きに向く。
	//						pa = Escape_NPC;
	//						NPCEscapeNumber = MyNumber;
	//						Chase_Zombie = ai;   //NPCからの逃走関数に使う。
	//					}
	//				}
	//			}
	//		}
	//
	//	});
	//	Player* pl = FindGO<Player>("Player");
	//	CVector3 v = m_position - pl->m_position;
	//	float len = v.Length();//長さ
	//	if (len < 60.0f) {//プレイヤーを見つけたら
	//		float angle = VectorAngleDeg(pl->m_position); //検索対象の座標を引数にする。
	//		if (angle <= 45.0f&&angle >= -45.0f) { //角度が視界内だったら
	//											   //プレイヤーから逃げる。
	//
	//			muki.x = m_forward.x*(-1);
	//			muki.y = m_forward.y*(-1);
	//			muki.z = m_forward.z*(-1);
	//			NPCEscapeNumber = MyNumber;
	//			pa = Escape_Player;
	//		}
	//	}
	//	//if (len < REACH) {//攻撃を受ける範囲まで近づいたら確実にダメージを受けるので
	//	//	DamageFlag = true;//ダメージフラグをtrueにする。
	//	//}
	//	//if (DamageFlag == true) {//プレイヤーからの攻撃を受けたら
	//	//	static int i = 0; //30フレームをカウントする。
	//	//	if (i >= 30) {
	//	//		pa = Damage;//30フレーム経過したらパターンをダメージに変える。
	//	//	}
	//	//	else {
	//	//		i++; //1フレーム経過をカウントする。
	//	//	}
	//	//	
	//	//}
}

void AI::NPCNormal_Search()//NPCの警戒処理。
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//長さ
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.1);
		pa = Escape;
	}
}

void AI::NPCResistance_NPC()//NPCゾンビへの抵抗に関する処理。オーバーライドさせる。
{
	pa = Damage;
}

void AI::NPCResistance_Player()//プレイヤーへの抵抗に関する処理。オーバーライドさせる。
{
	pa = Damage;
}

void AI::NPCDamage()
{
	static int i = 0; //30フレームをカウントする。
	if (i >= 30) {
		//30フレーム経過したらゾンビ化。
		pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
		Zonbe = 1;
	}
	else {
		i++; //1フレーム経過をカウントする。
	}

}
//void AI::NPCEscape_NPC() //NPCからの逃
//	static bool LostFlag = false;  //見失ったかどうかを示すフラグ。
//								   ///////////////////
//								   //逃走に関する処理。
//								   ///////////////////
//
//	float len = GetKyori(this->m_position, Chase_Zombie->m_position);
//	if (len >= 60) { //距離が60以上空いたら
//		LostFlag = true;
//	}
//	if (LostFlag == true) { //見失ったら
//
//							/////////////////////
//							//元の位置に戻る処理。
//							/////////////////////
//
//		if (NPCEscapeNumber == MyNumber) {//元の位置の番号に戻ったら
//			pa = Normal; //パターンをノーマルに変える。
//			LostFlag = false;//フラグを元に戻す。
//		}
//
//	}
//}
//void AI::NPCEscape_Player() //プレイヤーからの逃走
//{
//	///////////////////
//	//逃走に関する処理。
//	///////////////////
//
//	static bool LostFlag = false;  //見失ったかどうかを示すフラグ。
//	Player* pl = FindGO<Player>("Player");
//	float len = GetKyori(this->m_position, pl->m_position);
//	if (len >= 120) { //距離が120以上空いたら
//		LostFlag = true; //NPCはプレイヤーを見失う。
//	}
//	if (LostFlag == true) { //見失ったら
//
//							/////////////////////
//							//元の位置に戻る処理。
//							/////////////////////
//
//		if (NPCEscapeNumber == MyNumber) {//元の位置の番号に戻ったら
//			pa = Normal; //パターンをノーマルに変える。
//			LostFlag = false;//フラグを元に戻す。
//		}
//
//	}
void AI::NPCZombie_Normal()
{
	CVector3 v = game->siminUI[iNo]->K - m_position; //Kが次の目的地
	float len = v.Length();//長さ
	if (30 <= len) {
		float angle = VectorAngleDeg(v);
		if (angle >= 3.0) {
			v.y = 0.0f;
			v.Normalize();
			CVector3 forward = this->m_forward;
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(forward, v);
			rotAxis.Normalize();
			CQuaternion qBias1;
			qBias1.SetRotationDeg(rotAxis, 3.0f);
			m_rotation.Multiply(qBias1);
		}
		else {
			if (angle >= 2.0f) {
				v.y = 0.0f;
				v.Normalize();
				CVector3 forward = this->m_forward;
				//回転軸を求める。
				CVector3 rotAxis;
				rotAxis.Cross(forward, v);
				rotAxis.Normalize();
				CQuaternion qBias1;
				qBias1.SetRotationDeg(rotAxis, angle);
				m_rotation.Multiply(qBias1);
			}
			//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);//移動。
		}
	}
	else {
		if (ima >= 6)//今のポジションが6なら
					 //0にリセットする。0,1,2,3,4,5の順番。
			ima = 0;
		game->siminUI[iNo]->kyorikeisan(game->da[iNo][ima++] - 1);
	}
	/////////////////////////////////
	//一定のルートをうろうろする処理。
	/////////////////////////////////
	float min_Nagasa = 9999.0f;
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			AI* ai = (AI*)go;
			if (ai->Zonbe == 0) {   //それが一般市民だったら
				float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
				if (kyori < 60.0f) {  //距離が視界範囲以内だったら
					float angle = VectorAngleDeg(ai->m_position); //検索対象の座標を引数にする。
					if (angle <= 45.0f) { //角度が視界内だったら
						if (kyori < min_Nagasa) { //自分に一番近いのなら
							min_Nagasa = kyori;
							Tansaku = ai;
						}
					}
				}
			}
		}
	});

	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //パターンをゾンビチェイスに変える。
	}
}
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len>80.0f||HitFlag == true) {//他のNPCを見失った(距離が80以上あいた)、あるいは攻撃を与えたら
		//元の位置に戻る。
		if (ZombieChaseNumber == MyNumber) {//元の位置の番号に戻ったら
			Tansaku = nullptr; //検索結果を初期化する。
			pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
			HitFlag = false;
		}
	}else {//NPCを見失っておらず、見つけていたら
		CVector3 n = m_position - Tansaku->m_position;
		n.Normalize();
		n.y = 0.0f;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), n*m_speed);
			/////////////////////////////////
			//市民NPCを追跡する処理。
			/////////////////////////////////
		if (len<REACH) {//NPCに追いついたら
						//攻撃する(確実に当たる仕様)。
			NPC_Attack_Animation();//攻撃アニメーションを流す。
			HitFlag = true; //「NPCに攻撃を当てた」というフラグをたてる。
		}
	}	
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
void AI::NPCFade_Out()//一般市民が退場するときの処理。
{

	CVector3 v = game->siminUI[iNo]->K - m_position; //Kが次の目的地
	float len = v.Length();//長さ
	if (100 <= len) {
		float angle = VectorAngleDeg(v);
		if (angle >= 2.0) {//10度より上なら回転
			//パスまでベクトルをXZ平面上での向きにする。
			v.y = 0.0f;
			v.Normalize();
			CVector3 forward = this->m_forward;
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(forward, v);
			rotAxis.Normalize();
			CQuaternion qBias1;
			qBias1.SetRotationDeg(rotAxis, 3.0);
			m_rotation.Multiply(qBias1);
		}
		else {//10度未満でかつ-10度以上なら
			//	m_position += (game->siminUI[iNo]->bekutor)*m_speed;
			//if (angle != 0) {
			//	v.y = 0.0f;
			//	v.Normalize();
			//	CVector3 forward = this->m_forward;
			//	//回転軸を求める。
			//	CVector3 rotAxis;
			//	rotAxis.Cross(forward, v);
			//	rotAxis.Normalize();
			//	CQuaternion qBias1;
			//	qBias1.SetRotationDeg(rotAxis, angle);
			//	m_rotation.Multiply(qBias1);
			//}
			m_position =A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);//移動。
		}
		//}
		//v.Normalize();
		//m_position = m_charaCon.Execute(GameTime().GetFrameDeltaTime(), v*m_speed);//移動
	}
	else {//パスに着いたら
		if (da >= jyunban.size()) {//指定されたパスの最後まで着いたら
			pa = Death;
			da = 1;
		}
		else {
			game->siminUI[iNo]->kyorikeisan(jyunban[da++] - 1);
		}
	}
}

float AI::GetKyori(CVector3 a, CVector3 b) //2つのオブジェクトの座標を受け取り、オブジェクト間の距離を返す。
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

float AI::VectorAngleDeg2(CVector3 c)
{
	c.Normalize();//向きVectorにする。
	float kaku = atanf(c.Dot(m_rite));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree = CMath::RadToDeg(kaku);//求めたラジアンを度に変える。

	return degree;
}

float AI::Siya(CVector3 h, float g)
{

	if (g < 500.0f) {
		if (fabsf(VectorAngleDeg(h)) <= 45.0f) {//見つけたら
			retu_position = m_position;
			//m_speed = 1000.0f;
			//DamageFlag = true;
			//プレイヤーから逃げる。
			return 1;
		}
	}
	return 0;
}

float AI::VectorAngleDeg(CVector3 c)
{
	c.Normalize();//向きVectorにする。
	float kaku = acosf(c.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree =CMath::RadToDeg(kaku);

	return degree;
}

void AI::DamageHantei() //全てのゾンビと距離でダメージ判定をする。
{
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			AI* ai = (AI*)go;
			if (ai->Zonbe == 1) {   //それがゾンビだったら
				float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
				if (kyori < REACH) {  //距離が攻撃範囲以内だったら
					pa = Resistance_NPC; //パターンを抵抗にかえる。
				}
			}
		}
	});

	float kyori = GetKyori(this->m_position, pl->GetPosition());//自分との距離を求める。
	if (kyori < REACH) {  //距離が攻撃範囲以内だったら
		pa = Resistance_Player; //パターンを抵抗にかえる。
	}
}

void AI::NPCDeath()//死亡、消滅処理。
{
//	DeleteGO(this);//自己消滅。
}

void AI::Animation_Walk()//歩き始めと歩き続けの一連のアニメーションの処理。
{
	
}
void AI::Animation_Run()//走り始めと走り続けの一連のアニメーションの処理。
{

}

void AI::Start_Walk_Animation()//キャラクターが歩き始める時のアニメーションの処理。
{

}

void AI::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
{

}

void AI::Start_Run_Animation()//キャラクターが走り始める時のアニメーションの処理。
{

}

void AI::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
{

}

void AI::Resistance_Animation()//キャラクターが抵抗している時のアニメーションの処理。
{

}

void AI::NPC_Attack_Animation()//ゾンビ化キャラクターが攻撃している時のアニメーションの処理。
{

}


void AI::Update()
{
	//pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	k_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_rite.x = k_tekirot.m[0][0];
	m_rite.y = k_tekirot.m[0][1];
	m_rite.z = k_tekirot.m[0][2];
	m_rite.Normalize();
	
	if (muteki_Flag == true) {
		muteki_count++;
		if (muteki_count > 300) {//無敵化してから300フレームが経過したら
			muteki_Flag = false;
		}
	}

	if (Zonbe == 0) { //自分がゾンビではなかったら
		if (muteki_Flag == false) {//無敵ではなかったら
			DamageHantei(); //ゾンビとの当たり判定をとる。
		}
	}
	
	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == 0) {//特殊部隊が出現したら、
		ForceFlag = 1;//出現フラグを立てる。
	}
	if (ForceFlag == 1) {//特殊部隊が出現したら
		if (Zonbe == 1) {//自分がゾンビだったら
			pa = Zombie_Attack; //パターンをゾンビアタックに切り替える。
		}
		else {//尚且つ、自分がゾンビではなかったら
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu.m_pointList[0], &jyunban);
			game->siminUI[iNo]->kyorikeisan(jyunban[0] - 1);
			da = 1;
			m_speed = 100.0;
			pa = Fade_Out; //パターンをフェードアウトに切り替える。
		}
		ForceFlag = 2;//1回しか実行したくないのでフラグをさげる。

	}

	CQuaternion qBias;
	qBias = rotation(270);

	switch (pa) {
	case Normal:
		//NPCの動きを書く。
		NPCNormal();
		NPCNormal_Search();
		break;
	//case Escape_NPC:
	//	NPCEscape_NPC();
	//	break;
	//case Escape_Player:
	//	NPCEscape_Player();
	//	break;
	case Escape:
		NPCescape();
		break;
	case Return:
		NPCReturn();
		break;
	case Fade_Out:
		NPCFade_Out();
		break;
	case Resistance_NPC:
		NPCResistance_NPC();
		break;
	case Resistance_Player:
		NPCResistance_Player();
		break;
	case Damage:
		NPCDamage();
		break;
	case Zombie_Normal:
		NPCZombie_Normal();
		break;
	case Zombie_Chase:
		//他のNPCを見つけた時の処理を書く。
		//NPCZombie_Chase();
		break;
	case Zombie_Attack:
		//NPCZombie_Attack();
		break;
	case Death:
		NPCDeath();
		break;
	default:
		NPCZombie_Normal();
		break;
	}

	

	
	//Muve(m_movespeed);//ムーヴスピード入れると動く
	//m_movespeed.x += 0.001;
	// //qRot回転とキャラの回転を乗算して合成する。
	//qBias.Multiply(m_rotation, qBias);

	//NPCの前方向を計算

	//mRot.MakeRotationFromQuaternion(m_rotation);
	//m_forward.x = mRot.m[2][0];
	//m_forward.y = mRot.m[2][1];
	//m_forward.z = mRot.m[2][2];
	//m_forward.Normalize();
	//m_rite.x = mRot.m[0][0];
	//m_rite.y = mRot.m[0][1];
	//m_rite.z = mRot.m[0][2];
	//m_rite.Normalize();
	//m_position += m_forward *  m_speed;
	//m_position += m_rite * 10 * m_speed;		
	//CVector3 k = { 8881.04883
	//		,- 221.356491
	//		,9464.60547 };
	//	CVector3 b = {
	//		4190.29980
	//		,- 221.356491
	//		,4564.60596 };
	//	keiro=NewGO<keiroK>(0);


	//	keiro->tansa(k, b);
	m_skinModel.Update(m_position, m_rotation, { 0.5f, 0.5f,0.5f });
}
void AI::NPCReturn()
{
	int Size = jyunban.size();

	CVector3 v = game->siminUI[iNo]->K - m_position;
	float len = v.Length();//長さ
	if (300 <= len) {
		float angle = VectorAngleDeg(v);
		if (angle >= 2.0) {//10度より上なら回転
			v.y = 0.0f; //パスまでベクトルをXZ平面上での向きにする。
			v.Normalize();
			CVector3 forward = this->m_forward;
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(forward, v);
			rotAxis.Normalize();
			CQuaternion qBias1;
			qBias1.SetRotationDeg(rotAxis, 3.0);
			m_rotation.Multiply(qBias1);
		}
		else {
			//m_position += game->siminUI[iNo]->bekutor*m_speed;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_forward*m_speed);
		}
	}
	else {
		if (da >= Size) {//元の位置にもどった
			ima--;
			pa = Normal;//パターンをノーマルにかえる。
			da = 1;
		}
		else {
			game->siminUI[iNo]->kyorikeisan(jyunban[da++] - 1);
			modori = 0;
		}
	}
}
void AI::NPCescape()
{

	CVector3 v = m_position - pl->GetPosition();
	float len = v.Length();//長さ
	if (len < 2000.0) {
		v.Normalize();//正規化して向きベクトルにする。
		v.y = 0.0f;
		//m_position += v * m_speed;
		m_position =A_charaCon.Execute(GameTime().GetFrameDeltaTime(),v*m_speed);
	}

	else {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position,&jyunban);
		game->siminUI[iNo]->kyorikeisan(jyunban[0]-1);
		pa = Return;
	}
}
void AI::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
