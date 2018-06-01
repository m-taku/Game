#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"Pasu.h"
#include"tekihei.h"
#define REACH 300.0  //ゾンビの攻撃範囲。この距離まで近づいたら攻撃する。
#define PI 3.141592653589793 
//AI NPC;
//今回はmを引用するNPCのハンドルとして、jを特殊部隊のハンドルとして代用する。これは後に直しておくように。
//NPCとNPCゾンビの両方を処理する。
AI::AI()
{
	pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_speed = 1.0f; //ノーマル状態のときの常に動く移動速度（基本1）。
}
AI::~AI()
{
	//m_charaCon.RemoveRigidBoby();
	DeleteGO(work);
}
bool AI::Start()
{
	work = NewGO<AImove>(0, "AImove");
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	game=FindGO<Game>("Game");
	iNo = game->incNo();
	Leftfrag = game->GetLeft();
	if (Leftfrag <= 0) {
		pasu = game->getAIDate(iNo);
	}
	else
	{
		pasu = game->getLAIDate(iNo);
	}
	m_position= game->pasu[Leftfrag].m_pointList[pasu[ima++] - 1];
	
	m_position.y = 0.0f;
	//キャラのスキンモデルのロードは各自サブクラスで行う。
	m_skinModelData.Load(L"modelData/liam.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);

	//フラスタムカリングを初期化。
	m_objectFrustumCulling.Init(MainCamera());
	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	//A_charaCon.Init(
	//	10.0,			//半径。 
	//	100.0f,			//高さ。
	//	m_position,		//初期位置。
	//	0
	//);
	////アニメーションの初期化。
	//ai_NPCAnimation.Init(
	//	m_skinModel,			//アニメーションを流すスキンモデル。
	//								//これでアニメーションとスキンモデルが関連付けされる。
	//	ai_NPCAnimationClips,	//アニメーションクリップの配列。
	//	6							//アニメーションクリップの数。
	//);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();

	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		material->Setm_zonbi(zondi.GetBody());
	});
	m_rotation.SetRotationDeg(CVector3::AxisY,VectorAngleDeg(game->pasu[Leftfrag].m_pointList[pasu[ima] - 1]));
	SetTags(10);
	m_skinModel.SetShadowCasterFlag(true);
	if (game->GatNo() >= 20&& Leftfrag==0) {//AIが増えた時はここを増やす。
		game->risetteNo();
		game->SetLeft();
	}
	if (game->GatNo() >= 19 && Leftfrag == 1) {//左側のAIが増えたらこ↑こ↓を増やす。
		game->risetteNo();
	}
	/*ai_NPCAnimationClips[0].SetLoopFlag(false);
	ai_NPCAnimationClips[0].SetLoopFlag(true);
	ai_NPCAnimationClips[0].SetLoopFlag(false);
	ai_NPCAnimationClips[0].SetLoopFlag(true);
	ai_NPCAnimationClips[0].SetLoopFlag(true);
	ai_NPCAnimationClips[0].SetLoopFlag(false);*/

	return true;
}
void AI::NPCNormal()
{
	work->kyorikeisan(pasu[ima] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());//回転
	m_position += /*A_charaCon.Execute(*/ (m_forward*(work->Getmuve()*m_speed))*(GameTime().GetFrameDeltaTime());//移動

	if (15.0f > work->Getlen()) {
		if (Leftfrag <= 0) {


			if (ima >= game->gatsiz(iNo) - 1) {//今のポジションが6なら
						  //0にリセットする。0,1,2,3,4,5の順番。
				ima = 0;

			}
			else {
				ima++;
			}
		}
		else {
			if (ima >= game->gatLsiz(iNo) - 1) {//今のポジションが6なら
											   //0にリセットする。0,1,2,3,4,5の順番。
				ima = 0;

			}
			else {
				ima++;
			}
		}
	}
}
void AI::NPCNormal_Search()//NPCの警戒処理。
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//長さ
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.1);
		m_speed = 1.5f;
		pa = Escape;
	}
}

void AI::NPCResistance_NPC()//NPCゾンビへの抵抗に関する処理。オーバーライドさせる。
{
	if (sinsoku < 1.0) {
		m_skinModel.Satburend(sinsoku);
		sinsoku += 0.01;
	}
	else {
		pa = Damage;
	}
}

void AI::NPCResistance_Player()//プレイヤーへの抵抗に関する処理。オーバーライドさせる。
{
	if (sinsoku < 1.0) {
		m_skinModel.Satburend(sinsoku);
		sinsoku += 0.01;
	}
	else {
		pa = Damage;
	}
}

void AI::NPCDamage()
{
	static int i = 0; //30フレームをカウントする。
	if (i >= 30) {
		//30フレーム経過したらゾンビ化。
		pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
		m_speed = 1.5;
		Zonbe = 1;
	}
	else {
		i++; //1フレーム経過をカウントする。
	}

}

void AI::NPCZombie_Normal()
{

	NPCNormal();
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
		n=n*500.0;
		m_position += /*A_charaCon.Execute(*/ (n*(work->Getmuve()*m_speed))*(GameTime().GetFrameDeltaTime());//移動
			/////////////////////////////////
			//市民NPCを追跡する処理。
			/////////////////////////////////
		if (len<REACH) {//NPCに追いついたら
						//攻撃する(確実に当たる仕様)。
			//NPC_Attack_Animation();//攻撃アニメーションを流す。
			HitFlag = true; //「NPCに攻撃を当てた」というフラグをたてる。
		}
	}	
}
void AI::NPCZombie_Attack()//vs特殊部隊
{
	if (BattleFlag == false) {//部隊と戦っておらず、フリーな状態なら
		if (da >= jyunban.size()) {//指定されたパスの最後まで着いたら
			if (tekip->tekiheiflag[No] >= 1) {
				work->kyorikeisan(tekip->tekipos[No], m_position, m_forward);
			}
			else {
				takikennsau();
			}
		}
		else {
			work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
		}
		m_rotation.Multiply(work->Getkaku());
		CVector3 v = work->Getmokuteki() - m_position;  //一番近い部隊に移動する。
		m_position += /*A_charaCon.Execute(*/ m_forward * (work->Getmuve()*m_speed)*GameTime().GetFrameDeltaTime();//移動
		if (15.0f > work->Getlen()) {
			if (da >= jyunban.size() - 1) {//指定されたパスの最後まで着いたら
				if (tekip->tekiheiflag[No] >= 1) {
					da++;
				}
				else {
					takikennsau();
				}
			}
			else {
				da++;
			}
		}
		float h = 9999999999999.0f;
		for (int i = 0; i < 10; i++) {
			if (tekip->tekiheiflag[i] >= 1) {
				float max = GetKyori(m_position, tekip->tekipos[i]);
				if (max < REACH) {//部隊に近づいたら
					BattleFlag = true;//戦闘を開始する。
					if (h > max) {
						No = i;
						h = max;
					}
				}
			}
		}
	}
	if (BattleFlag == true) {//戦闘状態なら
		CVector3 bekutor = tekip->tekipos[No] - m_position;
		float len = GetKyori(m_position, tekip->tekipos[No]);
		float angle = VectorAngleDeg(bekutor);
		if (angle >= 3.0) {
			bekutor.y = 0.0f;
			bekutor.Normalize();
			//回転軸を求める。
			CVector3 rotAxis;
			rotAxis.Cross(m_forward, bekutor);
			rotAxis.Normalize();
			CQuaternion qBias1;
			qBias1.SetRotationDeg(rotAxis, 5.0f);
			m_rotation.Multiply(qBias1);
		}
		else if(150<len){
			m_position += /*A_charaCon.Execute(*/ m_forward *500 * m_speed*GameTime().GetFrameDeltaTime();
		}
		else {
			//殴る
			tekip->tekiHP[No] = tekip->tekiHP[No]-5;
     	 //部隊に攻撃する。
			takikennsau();
			BattleFlag = false;
		}
	}

	//if () {//部隊を倒したら
	//	//「戦闘を終了した」というフラグをたてる。
	//	BattleFlag = false;
	//}
	
}
void AI::takikennsau()
{
	float min = 99999999999999999.0;
	No = -1;
	if (tekip != NULL) {
		for (int i = 0; i < 10; i++) {
			if (tekip->tekiheiflag[i] >= 1) {
				float max = GetKyori(m_position, tekip->tekipos[i]);
				if (min > max) {
					min = max;
					No = i;
				}
			}
		}
		if (No >= 0) {
			CVector3 posa = tekip->tekipos[No] - m_position;
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, tekip->tekipos[No], &jyunban, Leftfrag);
			da = 0;//もう一度検索
		}
	}
}
void AI::NPCFade_Out()//一般市民が退場するときの処理。
{
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());
	m_position += /*A_charaCon.Execute(*/ (m_forward*(work->Getmuve()*m_speed))*(GameTime().GetFrameDeltaTime());//移動
	if (15.0f > work->Getlen()) {
		if (da >= jyunban.size()-1) {//指定されたパスの最後まで着いたら
			pa = Death;
			da = 1;
		}
		else {
			da++;
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
	c.y = 0.0f;
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
				if (kyori < 300) {  //距離が攻撃範囲以内だったら
					pa = Resistance_NPC; //パターンを抵抗にかえる。
				}
			}
		}
	});

	float kyori = GetKyori(this->m_position, pl->GetPosition());//自分との距離を求める。
	if (kyori < 300) {  //距離が攻撃範囲以内だったら
		pa = Resistance_Player; //パターンを抵抗にかえる。
	}
}

void AI::NPCDeath()//死亡、消滅処理。
{
	game->SatSaizon(iNo);
	DeleteGO(this);//自己消滅。
}
//
//void AI::Animation_Walk()//歩き始めと歩き続けの一連のアニメーションの処理。
//{
//	static int walk_count = 0;//歩き始めてからのカウント
//	if (work->Gatmuve()!=0) {
//		//動いていたら
//		if (walk_count<50) {
//			Start_Walk_Animation();
//		}
//		else {
//			Loop_Walk_Animation();
//		}
//		walk_count++;
//	}
//	else {//止まったら
//		walk_count = 0;
//	}
//	
//}
//void AI::Animation_Run()//走り始めと走り続けの一連のアニメーションの処理。
//{
//	static int run_count = 0;//走り始めてからのカウント
//	if (work->Gatmuve() != 0) {
//		//動いていたら
//		if (run_count<50) {
//			Start_Run_Animation();
//		}
//		else {
//			Loop_Run_Animation();
//		}
//		run_count++;
//	}
//	else {//止まったら
//		run_count = 0;
//	}
//}


//void AI::Start_Walk_Animation()//キャラクターが歩き始める時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Start_Walk);
//}
//
//void AI::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Loop_Walk);
//}
//
//void AI::Start_Run_Animation()//キャラクターが走り始める時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Start_Run);
//}
//
//void AI::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Loop_Run);
//}
//
//void AI::Resistance_Animation()//キャラクターが抵抗している時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Resistance);
//}
//
//void AI::NPC_Attack_Animation()//ゾンビ化キャラクターが攻撃している時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(NPC_Attack);
//}


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
			if (pa != Damage)
				DamageHantei(); //ゾンビとの当たり判定をとる。
		}
	}

	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == false) {//特殊部隊が出現したら、
		tekip = FindGO<tekihei>("tekihei");
		ForceFlag = true;//出現フラグを立てる。
		if (Zonbe == 1) {//自分がゾンビだったら
			takikennsau();
			pa = Zombie_Attack; //パターンをゾンビアタックに切り替える。
		}
		else {//尚且つ、自分がゾンビではなかったら
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
			da = 0;
			m_speed = 1.5;
			pa = Fade_Out; //パターンをフェードアウトに切り替える。
		}
	}


	switch (pa) {
	case Normal:
		//NPCの動きを書く。
		NPCNormal();
		NPCNormal_Search();
		break;
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
		NPCZombie_Attack();
		break;
	case Death:
		NPCDeath();
		break;
	default:
		NPCZombie_Normal();
		break;
	}
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			AI* ai = (AI*)go;
			CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
			float f = kyori1.Length();
			if (Siya(kyori1, f)) { //距離が攻撃範囲以内だったら
				kyori1 /= 3.0f;
				kyori1.y = 0.0f;
				m_position += /*A_charaCon.Execute(*/ kyori1 * m_speed*-1 * GameTime().GetFrameDeltaTime();//移動

			}
		}
	});	
	if (!m_objectFrustumCulling.IsCulling()) {
		m_skinModel.Update(m_position, m_rotation, { 20.0f, 20.0f,20.0f });
	}
	m_skinModel.UpdateBoundingBox();
	m_objectFrustumCulling.Execute(m_skinModel.GetBoundingBox());
}
void AI::NPCReturn()
{
	int Size = jyunban.size();
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());
	CVector3 v = work->Getmokuteki() - m_position;
	m_position += /*A_charaCon.Execute(*/ m_forward * (work->Getmuve()*m_speed)*GameTime().GetFrameDeltaTime();//移動
	if (15.0f > work->Getlen()) {
		if (da >= jyunban.size()-1) {//指定されたパスの最後まで着いたら
			pa = Normal;//パターンをノーマルにかえる。
			da = 0;
		}
		else {
			da++;
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
		m_position += /*A_charaCon.Execute(*/ v * (work->Getmuve()*m_speed)*GameTime().GetFrameDeltaTime();//移動

	}
	else {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position,&jyunban, Leftfrag);
		m_speed = 1.0;
		pa = Return;
	}
}
void AI::Render(CRenderContext& rc)
{
	if (m_objectFrustumCulling.IsCulling()) {
		//描画しないンゴ。
		return;
	}
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
