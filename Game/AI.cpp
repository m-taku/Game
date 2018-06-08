#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"Pasu.h"
#include"tekihei.h"
#define REACH 200.0  //ゾンビの攻撃範囲。この距離まで近づいたら攻撃する。
#define PI 3.141592653589793 
//AI NPC;
//今回はmを引用するNPCのハンドルとして、jを特殊部隊のハンドルとして代用する。これは後に直しておくように。
//NPCとNPCゾンビの両方を処理する。
AI::AI()
{
	pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_speed = 0.5f; //ノーマル状態のときの常に動く移動速度（基本0.8）。1.5が走る。
	iNo = game1->incNo();
	Leftfrag = game1->GetLeft();
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
	//キャラのスキンモデルのロードは各自サブクラスで行う。
	m_skinModelData.Load(L"modelData/liam.cmo");//プレイヤーを書け
	m_skinModel.Init(m_skinModelData);
	if (Leftfrag <= 0) {
		pasu = game->getAIDate(iNo);
	}
	else
	{
		pasu = game->getLAIDate(iNo);
	}
	m_position = game->pasu[Leftfrag].m_pointList[pasu[ima++] - 1];
	m_position.y = 100.0;
	//フラスタムカリングを初期化。
	m_objectFrustumCulling.Init(MainCamera());
	CMatrix mRot;
	//mRot.MakeRotationFromQuaternion();
	A_charaCon.Init(
		40.0,			//半径。 
		150.0f,			//高さ。
		m_position,		//初期位置。
		1
	);
	ai_NPCAnimationClips[0].Load(L"animData/shiminidle.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[0].SetLoopFlag(true);
	ai_NPCAnimationClips[1].Load(L"animData/shiminwalk.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[1].SetLoopFlag(true);
	ai_NPCAnimationClips[2].Load(L"animData/shiminrun.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[2].SetLoopFlag(true);

	//アニメーションの初期化。
	ai_NPCAnimation.Init(
		m_skinModel,			//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		ai_NPCAnimationClips,	//アニメーションクリップの配列。
		4							//アニメーションクリップの数。
	);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	work->Setkakudo(4.0f);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
		material->Setm_zonbi(zondi.GetBody());
	});
	m_rotation.SetRotationDeg(CVector3::AxisY,VectorAngleDeg(game->pasu[Leftfrag].m_pointList[pasu[ima] - 1]));
	SetTags(10);
	m_skinModel.SetShadowCasterFlag(true);


	return true;
}
void AI::NPCNormal()
{
	work->kyorikeisan(pasu[ima] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());//回転
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動

	if (160.0f > work->Getlen()) {
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
void AI::Zonbesiya()
{
	float min_Nagasa = 990099.0f;
	FindGameObjectsWithTag(10, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			AI* ai = (AI*)go;
			if (ai->GetZonbi()==false) {   //それが一般市民だったら
				float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
				if (kyori < 2.0f) {  //距離が視界範囲以内だったら
					float angle = VectorAngleDeg(this->m_position - ai->m_position); //検索対象の座標を引数にする。
					if (angle <= 100.0f) { //角度が視界内だったら
						if (kyori < min_Nagasa) { //自分に一番近いのなら
							min_Nagasa = kyori;
							Tansaku = ai;
						}
					}
				}
			}
		}
	});

	min_Nagasa;
}
void AI::NPCNormal_Search()//NPCの警戒処理。
{
	CVector3 v2 = pl->Getposition() - m_position;
	float len1 = v2.Length();//長さ
	float hann = Siya(v2, len1);
	if (hann == 1) {
		Gaizi->Satpoint(0.1);
		da = 0;
		m_speed = 2.5f;
		pa = Escape;
	}
	if (hann >= 2) {
		kannkaku = true;
	}
}

void AI::NPCResistance_NPC()//NPCゾンビへの抵抗に関する処理。オーバーライドさせる。
{
	m_speed = 0.0f;
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
	m_speed = 0.0f;
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
	static int count = 0; //30フレームをカウントする。
	if (count >= 30) {
		//30フレーム経過したらゾンビ化。
		nearestpas();
		SetZonbe();
	}
	else {
		count++; //1フレーム経過をカウントする。
	}

}
void AI::nearestpas()
{

	float sa = 99999999999999.0;
	for (int h = 0; h < game->pasu[Leftfrag].GetresutoSaiz()-1; h++) {
		CVector3 k = game->pasu[Leftfrag].Getresuto(h)->m_position[0] - m_position;
		float saa = k.Length();
		if (sa > saa) {
			sa = saa;
			mokuhyou = game->pasu[Leftfrag].Getresuto(h)->No[0];
		}
	}
	m_speed = 1.5;
	for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
		if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
			mokuhyouNo = ka;
			break;
		}
	}
	pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
}

void AI::NPCZombie_Normal()
{
	work->kyorikeisan(mokuhyou-1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());//回転
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動


	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - m_position).Length() < 150.0f) {
		int furag = 0;
		do {
			int num = Random().GetRandInt() % (game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No.size() - 1);
			if (mokuhyou != game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[++num]) {
				furag++;
				mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[num];
			}
		} while (furag == 0);
		for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
			if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
				mokuhyouNo = ka;
				break;
			}
		}
	}
	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //パターンをゾンビチェイスに変える。
	}
}
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len>2100.0f||HitFlag == true) {//他のNPCを見失った(距離が80以上あいた)、あるいは攻撃を与えたら
		//元の位置に戻る。
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
			Tansaku = nullptr; //検索結果を初期化する。
			kaiten = false;
			nearestpas();
			HitFlag = false;
		
	}else {//NPCを見失っておらず、見つけていたら
		CVector3 n =  Tansaku->m_position-m_position;
		NPCRunangle(n);
		n.y = 0.0f;
		n.Normalize();
		m_movespeed = n * (m_speed*200.0 + mobe);
		m_movespeed.y+=gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//移動
			/////////////////////////////////
			//市民NPCを追跡する処理。
			/////////////////////////////////
		if (len<REACH) {//NPCに追いついたら
						//攻撃する(確実に当たる仕様)。
			Tansaku->pa = Resistance_NPC;
			//NPC_Attack_Animation();//攻撃アニメーションを流す。
			HitFlag = true; //「NPCに攻撃を当てた」というフラグをたてる。
		}
	}	
}
void AI::NPCZombie_Attack()//vs特殊部隊
{
	if (tekip != NULL) {
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
			m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
			m_movespeed.y += gravity;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
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
			else if (150 < len) {
				m_movespeed = m_forward * (m_speed + mobe);
				m_movespeed.y += gravity;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
			}
			else {
				//殴る
				tekip->tekiHP[No] = tekip->tekiHP[No] - 5;
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
	m_movespeed = m_forward*(work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//移動
	if (200.0f > work->Getlen()) {
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
			if (pa == Normal)
				retu_position = m_position;
			//m_speed = 1000.0f;
			//DamageFlag = true;
			//プレイヤーから逃げる。
			return 1;
		}
		else {
			if (pl->GetMoveSpeed().Length() >= 500.0f)
			{
				CQuaternion kaku;
				kaku.SetRotationDeg(CVector3::AxisY, 30.0f);
				m_rotation.Multiply(kaku);
				return 2;
			}
		}
	}
	return 0;
}
void AI::NPCChase()
{
	m_speed = 2.5f;
	CVector3 mokuteki = lam->m_position-m_position  ;
	NPCRunangle(mokuteki);
	if (mokuteki.Length()<=200.0f&&lam->muteki_Flag==false) {
		m_speed = 1.1f;
		lam->NPCHP -= 10.0f;
		muteki_Flag = true;
	}
	else {
		mokuteki.y = 0.0f;
		mokuteki.Normalize();//正規化して向きベクトルにする。
		m_movespeed = mokuteki * (150 * m_speed + mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
	}
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
	AIrest++;

	for (; AIrest != Humans.end(); AIrest++) {
		if (this != (AI*)AIrest[0]) {
			AI* ai = (AI*)AIrest[0];

			float kyori = GetKyori(this->m_position, ai->m_position);
			if (kyori < 1000) {
				float angle = VectorAngleDeg(ai->m_position - this->m_position);
				if (angle <= 60)
				{
					if (ai->GetZonbi() == true) {
						lam = ai;
						for (AIrest = Humans.begin() + 1; AIrest != Humans.end(); AIrest++) {
							if (this != (AI*)AIrest[0]) {
								AI* ai = (AI*)AIrest[0];
								if (ai->GetZonbi() != true) {
									if (10000.0 >= (ai->m_position - m_position).Length())
									{
										mikata++;
										mikatalest.push_back(ai);

									}
								}
							}
						}
						if (mikata <= 2) {
							m_speed = 2.5f;
							retu_position = m_position;
							pa = Escape_NPC;
							mikatalest.clear();
						}
						else {
							for (int k = 0; k < mikatalest.size(); k++) {
								m_speed = 2.5f;
								mikatalest[k]->Chasefrag = 1;
								mikatalest[k]->pa = Chase;
								mikatalest[k]->lam = this->lam;
							}
						}
						break;
					}
					else {
						//市民同士の確認
					}
				}
			}
		}
	}
	
	
	//FindGameObjectsWithTag(10, [&](IGameObject* go) {
	//	if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
	//		AI* ai = (AI*)go;
	//		if (ai->Zonbe == 1) {   //それがゾンビだったら
	//			float kyori = GetKyori(this->m_position, ai->m_position);//自分との距離を求める。
	//			if (kyori < 1000) {
	//				float angle = VectorAngleDeg(this->m_position - ai->m_position);
	//				if (angle <= 60)
	//				{
	//					CVector3 j = this->m_position - ai->m_position;
	//					j.y = 0.0f;
	//					j.Normalize();
	//					m_movespeed = j * (m_speed *(mobe + 1000));
	//					m_movespeed.y += gravity;
	//					m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
	//					kannkaku = true;
	//				}
	//			}
	//		}
	//	}
	//});

	float kyori = GetKyori(this->m_position, pl->GetPosition());//自分との距離を求める。
	if (kyori < 100) {  //距離が攻撃範囲以内だったら
		pa = Resistance_Player; //パターンを抵抗にかえる。
	}
}

void AI::NPCDeath()//死亡、消滅処理。
{
	if (Leftfrag <= 0) {
		game->SatRSaizon(iNo);
	}
	else {
		game->SatLSaizon(iNo);
	}
	DeleteGO(this);//自己消滅。
}

void AI::AI_Animation()//AIのアニメーション制御
{
	if (m_speed<=1.0) {
		Loop_Walk_Animation();
	}
	if (m_speed > 1.0) {
		Loop_Run_Animation();
	}
}
void AI::Idle_Animation() //キャラクターが歩き続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(0, 0.2);
}


void AI::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(1,0.2);
}


void AI::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(2,0.2);
}

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

	AIrest = Humans.begin();
	m_movespeed = CVector3::Zero;
	//pa = Normal; //ここはプレイヤーの行動によって変化するようにする。
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.y = 0.0f;
	m_forward.Normalize();
	kannkaku = false;
	if (muteki_Flag == true) {
		muteki_count++;
		if (muteki_count > 300) {//無敵化してから300フレームが経過したら
			muteki_Flag = false;
		}
	}

	if (GetZonbi()==false) { //自分がゾンビではなかったら
		if (muteki_Flag == false) {//無敵ではなかったら
			if (pa != Damage)
				DamageHantei(); //ゾンビとの当たり判定をとる。
			if (pl->GetattackF() >= 1) {
				if ((pl->Getposition() - m_position).Length() <= 100.0f) {
					if (atekfrag > -90.0) {
						CQuaternion qBias1;
						qBias1.SetRotationDeg(CVector3::AxisX, -10.0f);
						m_rotation.Multiply(qBias1);
						m_speed = 0.0;
						atekfrag -= 10.0;
					}
					kannkaku = true;
				}
			}
		}
	}

	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == false) {//特殊部隊が出現したら、
		ForceFlag = true;//出現フラグを立てる。
		if (GetZonbi()==true) {//自分がゾンビだったら
			tekip = FindGO<tekihei>("tekihei");
			takikennsau();
			pa = Zombie_Attack; //パターンをゾンビアタックに切り替える。
		}
		else {//尚且つ、自分がゾンビではなかったら
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
			da = 0;
			m_speed = 2.5f;
			work->Setkakudo(3.0f);
			pa = Fade_Out; //パターンをフェードアウトに切り替える。
		}
	}
	if (NPCHP <= 0.0) {
		m_speed = 0.0f;
		CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisX, 10.0f);
		m_rotation.Multiply(qBias1);
		kannkaku = true;
	}
	if (atekfrag < 0.0&&kannkaku == false) {
		
		CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisX, 10.0f);
		m_rotation.Multiply(qBias1);
		atekfrag += 10.0;
		kannkaku = true;
	}

	if (kannkaku== false) {
		switch (pa) {
		case Normal:
			//NPCの動きを書く。
			NPCNormal_Search();
			if (kannkaku != true) {
			//	m_speed = 1.0;
				NPCNormal();
			}
			break;
		case Escape:
			NPCescape();
			break;
		case Escape_NPC:
			NPCEscape_NPC();
			break;
		case Return:
			NPCNormal_Search();
			if (kannkaku != true)
				NPCReturn();
			break;
		case Chase:
			NPCChase();
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
			Zonbesiya();
			NPCZombie_Normal();
			break;
		case Zombie_Chase:
			//他のNPCを見つけた時の処理を書く。
			NPCZombie_Chase();
			break;
		case Zombie_Attack:
			NPCZombie_Attack();
			break;
		case Zombie_Return:
			Zonbesiya();
			NPCzombie_Return();
			break;
		case Death:
			NPCDeath();
			break;
		default:
			break;
		}
	}

	
	if (pa != Zombie_Chase) {
		FindGameObjectsWithTag(10, [&](IGameObject* go) {
			if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
				AI* ai = (AI*)go;
				CVector3 kyori1 = ai->m_position - this->m_position;//自分との距離を求める。
				float f = kyori1.Length();
				if (f<100.0f) { //距離が
					kyori1 /= 3.0f;
					kyori1.y = 0.0f;
					m_movespeed = kyori1 * m_speed*-1;
					m_movespeed.y += gravity;
					m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//移動

				}
			}
		});
	}
	Setposition(m_position);

	if (!m_objectFrustumCulling.IsCulling()) {
		m_skinModel.Update(m_position, m_rotation, { 20.0f, 20.0f,20.0f });
	}

	AI_Animation();
	m_skinModel.UpdateBoundingBox();
	m_objectFrustumCulling.Execute(m_skinModel.GetBoundingBox());
}
void AI::NPCReturn()
{
	int Size = jyunban.size();
	if (Size > 0) {
		work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
		m_rotation.Multiply(work->Getkaku());
		CVector3 v = work->Getmokuteki() - m_position;
		m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//移動
		if (15.0f > work->Getlen()) {
			if (da >= jyunban.size() - 1) {//指定されたパスの最後まで着いたら
				pa = Normal;//パターンをノーマルにかえる。
				m_speed = 1.0f;
				da = 0;
			}
			else {
				da++;
			}
		}
	}
	else
	{
		m_speed = 1.0f;
		pa = Normal;
	}

}
void AI::NPCzombie_Return()
{
	NPCReturn();
	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //パターンをゾンビチェイスに変える。
	}
	if (pa == Normal) {
		pa = Zombie_Normal;
	}
}
void AI::NPCRunangle(CVector3 kyori)
{
	kyori.y = 0.0f;
	float angle = VectorAngleDeg(kyori);
	kyori.Normalize();//正規化して向きベクトルにする。
	CVector3 rotAxis;
	rotAxis.Cross(m_forward, kyori);
	rotAxis.Normalize();
	CQuaternion qBias1;
	if (angle >= escapecaku) {
		qBias1.SetRotationDeg(rotAxis, escapecaku);
		m_rotation.Multiply(qBias1);
		kaiten = false;
	}
	else if (kaiten != true) {
		qBias1.SetRotationDeg(rotAxis, angle);
		escapecaku = 2;
		m_rotation.Multiply(qBias1);
		kaiten = true;
	}
}
void AI::NPCescape()//ゾンビから逃げる
{

	CVector3 v = m_position - pl->GetPosition();
	float len = v.Length();//長さ
	if (len < 2000.0) {
		NPCRunangle(v);
		//m_position += v * m_speed;
		v.y = 0.0f;
		v.Normalize();
		m_movespeed = v * (150*m_speed +mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
	}
	else {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
		m_speed = 2.5f;
		escapecaku = 30.0f;
		mobe = 50.0f;
		work->Setkakudo(5.0f);
		kaiten = false;
		pa = Fade_Out;
	}
}
void AI::NPCEscape_NPC()
{
	CVector3 j = this->m_position - lam->m_position;
	NPCRunangle(j);
	if (j.Length() >= 1500) {
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
		escapecaku = 30.0f;
		pa = Return;
	}
	else {
		j.y = 0.0f;
		j.Normalize();//正規化して向きベクトルにする。
		m_movespeed = j * (300 * m_speed + mobe);
		m_movespeed.y += gravity;
		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
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
