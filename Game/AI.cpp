#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include"Geizi.h"
#include"Pasu.h"
#include"tekihei.h"
#include"car.h"
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
	//A_charaCon.RemoveRigidBoby();
	DeleteGO(work);
}
bool AI::Start()
{
	work = NewGO<AImove>(0, "AImove");
	pl = FindGO<Player>("Player");
	Gaizi = FindGO<Geizi>("Geizi");
	Car = FindGO<car>("car");
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
		0
	);
	ai_NPCAnimationClips[shiminidle].Load(L"animData/shiminidle.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminidle].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminwalk].Load(L"animData/shiminwalk.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminrun].Load(L"animData/shiminrun.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminrun].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminattack].Load(L"animData/playerattack.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminattack].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiwalk].Load(L"animData/playerwalk.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[Zonbiwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiattack].Load(L"animData/playerattack.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[Zonbiattack].SetLoopFlag(true);
	
	//アニメーションの初期化。
	ai_NPCAnimation.Init(
		m_skinModel,			//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		ai_NPCAnimationClips,	//アニメーションクリップの配列。

		animnum					//アニメーションクリップの数。
	);
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	work->Setkakudo(4.0f);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi1.dds");
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
	float min_Nagasa = 99999999.0f;
	for (AIrest = Humans.begin() + 1; AIrest != Humans.end(); AIrest++) {
		if (this != (AI*)AIrest[0]) {															    //自分からの距離を計測するため、検索結果から自分を除外する。
			AI* ai = (AI*)AIrest[0];
			if (ai->GetZonbi() == false) {															//それが一般市民だったら
				if (ai->Raifu_f == false) {														    //その人が生きていれば
					float kyori = GetKyori(this->m_position, ai->m_position);						//自分との距離を求める。
					if (kyori < 1500.0f) {															//距離が視界範囲以内だったら
						float angle = VectorAngleDeg(ai->m_position - this->m_position);		    //検索対象の座標を引数にする。
						if (angle <= 60.0f) {														//角度が視界内だったら
							if (kyori < min_Nagasa) {												//自分に一番近いのなら
								min_Nagasa = kyori;
								Tansaku = ai;
							}
						}
					}
				}
			}
		}
	}
	if (ForceFlag == true) {
		float len = takikennsau();
		if (len <= 1500) {
			pa = Zombie_Attack;
			kannkaku = true;
		}
	}
}
void AI::NPCNormal_Search()//NPCの警戒処理。
{
	CVector3 v2 = pl->Getposition() - m_position;
	float len1 = v2.Length();//長さ
	float hann = Siya(v2, len1);
	if (hann == 1) {
		da = 0;
		m_speed = 4.0f;
		nearestpas();
		Fardist_path(pl->Getposition());
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
		lam = nullptr;
		Chasefrag = 0;
		Raifu_f = false;
		SetZonbe();
		NPCHP = 100.0f;
		NPCMAXHP = 100.0f;
		m_speed = 1.5;
		pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
	}
	else {
		count++; //1フレーム経過をカウントする。
	}

}
void AI::nearestpas()//最寄りのパス検索
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
	for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
		if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
			mokuhyouNo = ka;
			break;
		}
	}
}

void AI::NPCZombie_Normal()
{
	//	work->kyorikeisan(mokuhyou-1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	//	m_rotation.Multiply(work->Getkaku());//回転
	//	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	//	m_movespeed.y += gravity;
	//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
	pasmove();
	m_rotation.Multiply(work->Getkaku());//回転
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - m_position).Length() < 150.0f) {//ランダム徘徊のパス番号検索
		int num = Random().GetRandInt() % (game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No.size() - 1);
		mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[++num];
	}
	Retrieval_pasNo(mokuhyou);
	if (Tansaku != nullptr) {
		pa = Zombie_Chase; //パターンをゾンビチェイスに変える。
	}
}
void AI::NPCZombie_Attack()//vs特殊部隊
{

	static int flame = 40;
	if (tekip != NULL) {
		float len = GetKyori(m_position, tekip->tamapos[No]);
		if (len > 2100.0f &&tekip->tekiheiflag[No] <= 0) {//他のNPCを見失った(距離が2100以上あいた)、あるいは死んだら
														//元の位置に戻る。
			// //検索結果を初期化する。
			kaiten = false;
			HitFlag = false;
			escapecaku = 30.0f;
			nearestpas();
		}
		else {//NPCを見失っておらず、見つけていたら
			kannkaku=true;
			CVector3 n = tekip->tamapos[No] - m_position;
			NPCRunangle(n);
			if (len < atakkukyori) {//NPCに追いついたら
									//攻撃する(確実に当たる仕様)。
				HitFlag = true;//「NPCに攻撃を当てた」というフラグをたてる。
				if (flame >= 40) {
					tekip->tekiHP[No] -=3;
					flame = 0;
				}
				atakkukyori = 200.0f;
				//NPC_Attack_Animation();//攻撃アニメーションを流す。
			}
			else {
				HitFlag = false;
				n.y = 0.0f;
				n.Normalize();
				m_movespeed = n * (m_speed*200.0 + mobe);
				m_movespeed.y += gravity;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
				atakkukyori = 100.0f;
				/////////////////////////////////
				//市民NPCを追跡する処理。
				/////////////////////////////////
			}
		}
		flame++;
		//if (BattleFlag == false) {//部隊と戦っておらず、フリーな状態なら
		//	if (da >= jyunban.size()) {//指定されたパスの最後まで着いたら
		//		if (tekip->tekiheiflag[No] >= 1) {
		//			work->kyorikeisan(tekip->tekipos[No], m_position, m_forward);
		//		}
		//		else {
		//			takikennsau();
		//		}
		//	}
		//	else {
		//		work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
		//	}
		//	m_rotation.Multiply(work->Getkaku());
		//	CVector3 v = work->Getmokuteki() - m_position;  //一番近い部隊に移動する。
		//	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
		//	m_movespeed.y += gravity;
		//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
		//	if (15.0f > work->Getlen()) {
		//		if (da >= jyunban.size() - 1) {//指定されたパスの最後まで着いたら
		//			if (tekip->tekiheiflag[No] >= 1) {
		//				da++;
		//			}
		//			else {
		//				takikennsau();
		//			}
		//		}
		//		else {
		//			da++;
		//		}
		//	}
		//	float h = 9999999999999.0f;
		//	for (int i = 0; i < 10; i++) {
		//		if (tekip->tekiheiflag[i] >= 1) {
		//			float max = GetKyori(m_position, tekip->tekipos[i]);
		//			if (max < REACH) {//部隊に近づいたら
		//				BattleFlag = true;//戦闘を開始する。
		//				if (h > max) {
		//					No = i;
		//					h = max;
		//				}
		//			}
		//		}
		//	}
		//}
		//if (BattleFlag == true) {//戦闘状態なら
		//	CVector3 bekutor = tekip->tekipos[No] - m_position;
		//	float len = GetKyori(m_position, tekip->tekipos[No]);
		//	float angle = VectorAngleDeg(bekutor);
		//	if (angle >= 3.0) {
		//		bekutor.y = 0.0f;
		//		bekutor.Normalize();
		//		//回転軸を求める。
		//		CVector3 rotAxis;
		//		rotAxis.Cross(m_forward, bekutor);
		//		rotAxis.Normalize();
		//		CQuaternion qBias1;
		//		qBias1.SetRotationDeg(rotAxis, 5.0f);
		//		m_rotation.Multiply(qBias1);
		//	}
		//	else if (150 < len) {
		//		m_movespeed = m_forward * (m_speed + mobe);
		//		m_movespeed.y += gravity;
		//		m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
		//	}
		//	else {
		//		//殴る
		//		tekip->tekiHP[No] = tekip->tekiHP[No] - 5;
		//		//部隊に攻撃する。
		//		takikennsau();
		//		BattleFlag = false;
		//	}
		//}

		//if () {//部隊を倒したら
		//	//「戦闘を終了した」というフラグをたてる。
		//	BattleFlag = false;
		//}
	}
	
}
float AI::takikennsau()
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
	}
	return min;
}
void AI::NPCFade_Out()//一般市民が退場するときの処理。
{
	work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_rotation.Multiply(work->Getkaku());
	m_movespeed = m_forward*(work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//移動
	if (150.0f > work->Getlen()) {
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
float AI::VectorAngleDeg(CVector3 c)
{
	c.y = 0.0f;
	c.Normalize();//向きVectorにする。
	float kaku = acosf(c.Dot(m_forward));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree =CMath::RadToDeg(kaku);

	return degree;
}
float AI::VectorAngleDeg(CVector3 h,CVector3 c)
{
	c.y = 0.0f;
	c.Normalize();//向きVectorにする。
	h.y = 0.0f;
	h.Normalize();
	float kaku = acosf(c.Dot(h));//２つのべクトルの内積のアークコサインを求める。(ラジアン)

	float degree = CMath::RadToDeg(kaku);

	return degree;
}
void AI::NPC_Search_Zonbi() //全てのゾンビと距離でダメージ判定をする。
{
	AIrest++;
	if (Chasefrag <= 0) {
		for (; AIrest != Humans.end(); AIrest++) {
			if (this != (AI*)AIrest[0]) {
				AI* ai = (AI*)AIrest[0];
				float kyori = GetKyori(this->m_position, ai->m_position);
				if (kyori < 800) {
					float angle = VectorAngleDeg(ai->m_position - this->m_position);
					if (angle <= 60)
					{
						if (ai->GetZonbi() == true) {
							keikai_f = true;
							lam = ai;
							nearestpas();
							pa = Escape_NPC;
							m_speed = 3.0f;
							retu_position = m_position;
						}
					}
				}
				else {
					//市民同士の確認
				}
			}
		}
	}
	if (keikai_f==true) {
		for (AIrest = Humans.begin() + 1; AIrest != Humans.end(); AIrest++) {
			if (this != (AI*)AIrest[0]) {
				AI* ai = (AI*)AIrest[0];
				if (ai->GetZonbi() != true) {
					if (1000.0 >= (ai->m_position - this->m_position).Length())
					{
						mikata++;
						mikatalest.push_back(ai);
					}
				}
			}
		}
		if (mikata >= 2) {
			Chasefrag = 1;
			pa = Chase;
			keikai_f = false;
			retu_position = m_position;
			for (int k = 0; k < mikatalest.size(); k++) {
				m_speed = 4.0f;
				mikatalest[k]->Chasefrag += 1;
				mikatalest[k]->retu_position = mikatalest[k]->m_position;
				mikatalest[k]->pa = Chase;
				mikatalest[k]->keikai_f = false;
				mikatalest[k]->lam = this->lam;
			}
		}
		mikatalest.clear();
		mikata = 0;
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
	if (pl->GetattackF() >= 1) {
		if ((pl->Getposition() - m_position).Length() <= 100.0f) {
			m_speed = 0.0;
			NPCHP -= 1000.0f;
			HitFlag = false;
		}
	}
}
void AI::NPCDeath()//死亡、消滅処理。
{
	static int fureme = 0;
	if (Leftfrag <= 0) {
		game->SatRSaizon(iNo);
	}
	else {
		game->SatLSaizon(iNo);
	}
	if (fureme++ >= 30) {
		DeleteGO(this);//自己消滅。
	}
}

void AI::AI_Animation()//AIのアニメーション制御
{
	/*if (m_speed <= 1.0) {
		Loop_Walk_Animation();
	}
	if (m_speed > 1.0) {
		Loop_Run_Animation();
	}*/
	if (GetZonbi()==false) {
		if (HitFlag == true)
		{
				NPC_Attack_Animation();
			
		}else if (m_speed < 0.5f) {
			Idle_Animation();
		}
		else if (m_speed <= 1.0) {
			Loop_Walk_Animation();
		}
		else if (m_speed > 1.0) {
			Loop_Run_Animation();
		}

	}
	else {
		if (HitFlag == true)
		{
				NPC_Attack_Animation();
		}
		else if (m_speed >= 1.0f) {
			Zombie_Walk_Animation();
		}
	}
}

//void AI::Resistance_Animation()//キャラクターが抵抗している時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Resistance);
//}
//
void AI::NPC_Attack_Animation()//ゾンビ化キャラクターが攻撃している時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminattack, 0.2);
}


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
	if (GetZonbi() == false) { //自分がゾンビではなかったら
		if (muteki_Flag == false) {//無敵ではなかったら
			if (Raifu_f == false) {
				NPC_Search_Zonbi(); //ゾンビとの当たり判定をとる。
			}
		}
	}
	else {
		if (Pad(0).IsTrigger(enButtonY))
		{
			pa = Zonbie_Gathered;
		}
	}

	if (muteki_Flag == true) {
		muteki_count++;
		/*CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisY, 10.0f);
		m_rotation.Multiply(qBias1);*/
		//kannkaku = true;
		if (muteki_count > 30) {//無敵化してから300フレームが経過したら
			muteki_Flag = false;
			muteki_count = 0;
		}
	}
	else {
		if (NPCHP != NPCMAXHP) {
			muteki_Flag = true;
			NPCMAXHP = NPCHP;
		}
	}

	FindGameObjectsWithTag(20, [&](IGameObject* go) {
		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
			car* ai = (car*)go;
			CVector3 kyori1 = ai->Getposition() - this->m_position;//自分との距離を求める。
			float f = kyori1.Length();
			if (f <= 1000000) { //距離が車間距離よりも短くなっていたら
				float kaku = acosf(kyori1.Dot(ai->Getforward()));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
				float degree = CMath::RadToDeg(kaku);
				if (degree <= 90) {
					nearestpas();
					m_movespeed.y = 1000.0f;
					pa = flyNPC;
				}
			}
		}

	});
	if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == false) {//特殊部隊が出現したら、
		ForceFlag = true;//出現フラグを立てる。
		if (GetZonbi() == true) {//自分がゾンビだったら
			tekip = FindGO<tekihei>("tekihei");
			takikennsau(); //パターンをゾンビアタックに切り替える。
		}
		else {//尚且つ、自分がゾンビではなかったら
			jyunban.erase(jyunban.begin(), jyunban.end());
			keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
			da = 0;
			m_speed = 4.0f;
			work->Setkakudo(3.0f);
			pa = Fade_Out; //パターンをフェードアウトに切り替える。
		}
	}
	if (NPCHP <= 0.0&&Raifu_f==false) {//ＨＰがなくなってしまったら
		Raifu_f = true;							//死んでしまうとはなさけない！！
		if (GetZonbi() == false) {				//ゾンビではないなら
			pa = Resistance_NPC;				//もう一度チャンスをやろう！！！！
			escapecaku = 30.0f;
			m_speed = 0.0f;
			HitFlag = false;
		}
		else {
			NPCHP = 10.0f;//ゾンビなら......
			pa = Death;
		}
	//	kannkaku = true;
		//DeleteGO(this);
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
		case flyNPC:
			FlyNPC();
			break;
		case Fade_Out:
			NPCNormal_Search();
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
		case Zonbie_Gathered:
			Gathered();
			break;
		case Zombie_Normal:
			Zonbesiya();
			if (kannkaku != true) {
				NPCZombie_Normal();
			}
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
					kyori1 /= 5.0f;
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
void AI::FlyNPC()
{
	work->kyorikeisan(mokuhyou - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	CQuaternion kak;
	kak.SetRotationDeg(CVector3::AxisX, 30.0f);
	m_rotation.Multiply(kak);
	m_movespeed+=work->Getbekutor();
	CharaConUpdate();
	if (m_position.y <= 0.0f) {
		pa = Zombie_Normal;
	}
}
void AI::CharaConUpdate()
{
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
}
void AI::Gathered()                       //主人のところにいくぞ～～～
{
	jyunban.erase(jyunban.begin(), jyunban.end());
	keiro.tansa(m_position, pl->Getposition(), &jyunban, Leftfrag);
	
	pa = Zombie_Return;
}
void AI::NPCzombie_Return()               //目的地にいくんだ～～～
{
	NPCReturn();

	if (Tansaku != nullptr) {
		pa = Zombie_Chase;					//獲物だ～～～～（人を見つけた）
	}
	if (pa == Normal) {
		nearestpas();
		m_speed = 1.2;
		pa = Zombie_Normal;					//ついた～～～（ランダム徘徊開始）
	}
}
void AI::NPCRunangle(CVector3 kyori)//直線ベクトルをそのまま使った移動の際の、回転関数
{
	kyori.y = 0.0f;
	float angle = VectorAngleDeg(kyori);
	kyori.Normalize();//正規化して向きベクトルにする。
	CVector3 rotAxis;
	rotAxis.Cross(m_forward, kyori);
	rotAxis.Normalize();
	CQuaternion qBias1;
	if (angle >= 30) {
		escapecaku = 30.0f;
	}
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
void AI::pasmove()
{
	work->kyorikeisan(mokuhyou - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
}
void AI::Fardist_path(CVector3 m_position)//視野付きリンク先パス検索
{
	CVector3 minkore = { 0.0f,0.0f,0.0f };
	for (int Linknum = 0; Linknum < game->pasu[Leftfrag].GetresutoSaiz(mokuhyouNo); Linknum++) {
		CVector3 ma = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[Linknum] - m_position;
		if (minkore.Length() < ma.Length()) {
			if (90 <= VectorAngleDeg(ma, m_position - this->m_position)) {
				minkore = ma;
				mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[Linknum];
			}
		}
	}
	Retrieval_pasNo(mokuhyou);
}
void AI::hinannpas(CVector3 m_position)
{
	pasmove();
	NPCRunangle(work->Getbekutor());
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - this->m_position).Length() < 200.0f) {
		Fardist_path(m_position);
	}
}
void AI::NPCescape()//ゾンビから逃げる
{
	CVector3 v = m_position - pl->Getposition();
	v.y = 0.0f;
	float len = v.Length();//長さ
	if (len < 10000.0) {
		hinannpas(pl->Getposition());
	}
	else {
		jyunban.erase(jyunban.begin(), jyunban.end());     //逃げ切ったぜ～～～～
		keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
		m_speed = 4.0f;
		escapecaku = 30.0f;
		mobe = 50.0f;
		Gaizi->Satpoint(0.1);
		work->Setkakudo(5.0f);
		kaiten = false;
		pa = Fade_Out;										//こんな町......もうおさらばだ！！
	}
	//CVector3 v = m_position - pl->GetPosition();
	//float len = v.Length();//長さ
	//if (len < 2000.0) {
	//	NPCRunangle(v);							
	//	//m_position += v * m_speed;
	//	v.y = 0.0f;
	//	v.Normalize();			//に～げるんだよ～～～～
	//	m_movespeed = v * (150*m_speed +mobe);
	//	m_movespeed.y += gravity;
	//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
	//}


}
void AI::NPCEscape_NPC()
{
	CVector3 j = this->m_position - lam->m_position;
	if (j.Length() >= 3000) {
		jyunban.erase(jyunban.begin(), jyunban.end());				//もうゾンビいないやろ！！！
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
		escapecaku = 30.0f;											//元の位置に、も～～どろ
		pa = Return;
	}
	else {
		hinannpas(lam->m_position);
		//1人では戦えない！！！//に～げるんだよ～～～～
	}
}
void AI::search()
{
	jyunban.erase(jyunban.begin(), jyunban.end());     //逃げ切ったぜ～～～～
	keiro.tansa(m_position, game->pasu[Leftfrag].m_pointList[0], &jyunban, Leftfrag);
}
void AI::Retrieval_pasNo(int mokuhyou)
{
	for (int ka = 0; ka < game->pasu[Leftfrag].GetresutoSaiz(); ka++) {
		if (game->pasu[Leftfrag].Getresuto(ka)->No[0] == mokuhyou) {
			mokuhyouNo = ka;
			break;
		}
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
