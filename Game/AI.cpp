#include "stdafx.h"
#include"AImove.h"
#include"keiroK.h"
#include "AI.h"
#include "Player.h"
#include"Game.h"
#include "AI_manager.h"
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
	iNo = AI_ado->incNo();
	Leftfrag = AI_ado->GetLeft();
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
	bgm = FindGO<BGM>("BGM");
	//キャラのスキンモデルのロードは各自サブクラスで行う。
	//m_skinModelData.Load(L"modelData/liam.cmo");//プレイヤーを書け
	//m_skinModel.Init(m_skinModelData);
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
		30.0,			//半径。 
		150.0f,			//高さ。
		m_position,		//初期位置。
		0
	);
	//m_skinModelData.Load(L"modelData/liam.cmo");//男性型を書け
	//m_skinModel.Init(m_skinModelData);
	//ai_NPCAnimationClips[shiminidle].Load(L"animData/shiminidle.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[shiminidle].SetLoopFlag(true);
	//ai_NPCAnimationClips[shiminwalk].Load(L"animData/shiminwalk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[shiminwalk].SetLoopFlag(true);
	//ai_NPCAnimationClips[shiminrun].Load(L"animData/shiminrun.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[shiminrun].SetLoopFlag(true);
	//ai_NPCAnimationClips[shiminattack].Load(L"animData/playerattack.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[shiminattack].SetLoopFlag(true);
	//ai_NPCAnimationClips[Zonbiwalk].Load(L"animData/playerwalk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[Zonbiwalk].SetLoopFlag(true);
	//ai_NPCAnimationClips[Zonbiattack].Load(L"animData/playerattack.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[Zonbiattack].SetLoopFlag(true);
	//ai_NPCAnimationClips[Zonbi_zico].Load(L"animData/liam_ziko.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[Zonbi_zico].SetLoopFlag(false);

	////アニメーションの初期化。
	//ai_NPCAnimation.Init(
	//	m_skinModel,			//アニメーションを流すスキンモデル。
	//							//これでアニメーションとスキンモデルが関連付けされる。
	//	ai_NPCAnimationClips,	//アニメーションクリップの配列。

	//	animnum					//アニメーションクリップの数。
	//);
	//zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi1.dds");
	//m_skinModel.FindMaterial([&](CModelEffect* material) {
	//	material->Setm_zonbi(zondi.GetBody());
	//});
	m_tekirot.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = m_tekirot.m[2][0];
	m_forward.y = m_tekirot.m[2][1];
	m_forward.z = m_tekirot.m[2][2];
	m_forward.Normalize();
	work->Setkakudo(4.0f);
	m_rotation.SetRotationDeg(CVector3::AxisY,VectorAngleDeg(game->pasu[Leftfrag].m_pointList[pasu[ima] - 1]));
	SetTags(10);
	m_skinModel.SetShadowCasterFlag(true);
	return true;
}
void AI::NPCNormal()
{
	pasmove(pasu[ima]);
	m_rotation.Multiply(work->Getkaku());//回転
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
		bgm->SetZombie();//BGMのインスタンスにゾンビが増えたことを伝える。
		nearestpas();
		lam = nullptr;
		Chasefrag = 0;
		Raifu_f = false;
		SetZonbe();
		NPCHP = 100.0f;
		NPCMAXHP = 100.0f;
		m_speed = 1.5;
		//登録されているNPCが3DSMAX上で左側のパスに属していなかったら(右側のパスに属していたら)
		if (Leftfrag <= 0) {
			//右側に属するNPCの生存判定を初期化する(0で生存、-1で消滅)。
			game->SatRSaizon(iNo,0);
		}
		else {
			//左側に属するNPCの生存判定を初期化する(0で生存、-1で消滅)。
			game->SatLSaizon(iNo,0);
		}
		pa = Zombie_Normal; //パターンをゾンビノーマルに変える。
	}
	else {
		count++; //1フレーム経過をカウントする。
	}

}
void AI::nearestpas()//最寄りのパス検索
{
	float sa = 99999999999999.0;
	for (int h = 0; h < game->pasu[Leftfrag].GetresutoSaiz() - 1; h++) {
		CVector3 k = game->pasu[Leftfrag].Getresuto(h)->m_position[0] - m_position;
		float saa = k.Length();
		if (sa > saa) {
			sa = saa;
			mokuhyou = game->pasu[Leftfrag].Getresuto(h)->No[0];
		}
	}
	Retrieval_pasNo(mokuhyou);
}
float AI::takikennsau()
{
	float min = 99999999999999999.0;
	No = -1;
	if (tekip != NULL) {
		for (int i = 0; i < 45; i++) {
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
	m_movespeed = m_forward*(work->Getmuve()*m_speed + mobe* GameTime().GetFrameDeltaTime());
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(),m_movespeed);//移動
	if (30.0f > work->Getlen()) {
		if (da >= jyunban.size()-1) {//指定されたパスの最後まで着いたら
			pa = Death;
			da = 0;
		}
		else {
			da++;
		}
	}
}

//2つのオブジェクトの座標を受け取り、オブジェクト間の距離を返す。
float AI::GetKyori(CVector3 a, CVector3 b) 
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
							if (ai->Raifu_f == false) {
								keikai_f = true;
								lam = ai;
								nearestpas();
								pa = Escape_NPC;
								m_speed = 3.0f;
								retu_position = m_position;
								break;
							}
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
			search(lam->m_position);
			Retrieval_pasNo(mokuhyou);
			for (int k = 0; k < mikatalest.size(); k++) {
				m_speed = 3.0f;
				mikatalest[k]->Chasefrag += 1;
				mikatalest[k]->retu_position = mikatalest[k]->m_position;
				mikatalest[k]->pa = Chase;	
				mikatalest[k]->m_speed = 3.0f;
				mikatalest[k]->keikai_f = false;
				mikatalest[k]->lam = this->lam;
				mikatalest[k]->search(lam->m_position);
				mikatalest[k]->Retrieval_pasNo(mokuhyou);
			}
		}
		mikatalest.clear();
		mikata = 0;
	}
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

	if (fureme++ >= 30) {
		if (Leftfrag <= 0) {
			game->SatRSaizon(iNo,-1);
		}
		else {
			game->SatLSaizon(iNo,-1);
		}
		CQuaternion qBias1;
		qBias1.SetRotationDeg(CVector3::AxisX, 10.0f);
		m_rotation.Multiply(qBias1);
		//DeleteGO(this);//自己消滅。
	}
}



//void AI::Resistance_Animation()//キャラクターが抵抗している時のアニメーションの処理。
//{
//	ai_NPCAnimation.Play(Resistance);
//}
//
void AI::Update()
{
	AIrest = Humans.begin();
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
		if (muteki_count > 60) {//無敵化してから300フレームが経過したら
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
	//if (GetZonbi() == true&&pa!= flyNPC) {
	//	FindGameObjectsWithTag(20, [&](IGameObject* go) {
	//		if (go != this) {            //自分からの距離を計測するため、検索結果から自分を除外する。
	//			car* ai = (car*)go;
	//			CVector3 kyori1 = this->m_position- ai->Getposition();//自分との距離を求める。
	//			float f = kyori1.Length();
	//			if (f <= 600) { //距離が車間距離よりも短くなっていたら
	//				kyori1.Normalize();
	//				float kaku = acosf(kyori1.Dot(ai->Getforward()));//２つのべクトルの内積のアークコサインを求める。(ラジアン)
	//				float degree = CMath::RadToDeg(kaku);
	//				if (degree <= 45) {
	//					ziko_car = ai;
	//					pa = flyNPC;
	//				}
	//			}
	//		}
	//	});
	//}
	if (Gaizi != nullptr) {
		if (Gaizi->GatFragu() >= 1.0f&& ForceFlag == false) {//特殊部隊が出現したら、
			ForceFlag = true;//出現フラグを立てる。
			if (GetZonbi() != true)
			{//自分がゾンビではなかったら
				search(game->pasu[Leftfrag].m_pointList[0]);
				da = 0;
				m_speed = 4.0f;
				work->Setkakudo(3.0f);
				pa = Fade_Out; //パターンをフェードアウトに切り替える。
			}
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

//	AI_Animation();
	if (!m_objectFrustumCulling.IsCulling()) {
		m_skinModel.Update(m_position, m_rotation, { 20.0f, 20.0f,20.0f });
	}

	m_skinModel.UpdateBoundingBox();
	m_objectFrustumCulling.Execute(m_skinModel.GetBoundingBox());
}

void AI::NPCReturn()
{
	int Size = jyunban.size();
	if (Size > 1) {
		work->kyorikeisan(jyunban[da] - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
		m_rotation.Multiply(work->Getkaku());
		m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe* GameTime().GetFrameDeltaTime());
		CharaConUpdate();
		if (150.0f > work->Getlen()) {
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
	if (ziko_frag == false) {
		CVector3 kori = ziko_car->Getposition()- this->m_position;
		if (kori.Length() <= 300) {
			CVector3 tobu= this->Getforward()*-1;
			flydist =/* ziko_car->Getforward() +*/ tobu;
			flydist.y = 0.0f;
			flydist = { flydist.x*1000.0f,flydist.y,flydist.z*1000.0f };
			//flydist /= (1.0f / GameTime().GetFrameDeltaTime());
			m_movespeed = flydist;
			ziko_frag = true;
			m_movespeed.y = 600.0f;
			retu_position = game->pasu[Leftfrag].m_pointList[pasu[ima] - 1];
		}
		else if(kori.Length()>=1000)
		{
			pa = Zombie_Normal;
		}
		else {
			NPCRunangle(kori);
		}
	}
	else {
		//flydist /= 10;	
		if (A_charaCon.IsOnGround() && taime++ >= 2) {
			//pa = Zombie_Normal;
			m_movespeed = CVector3::Zero;
			//taime = 0;
		}
	}
	CharaConUpdate();	
}
void AI::CharaConUpdate()
{
	m_movespeed.y += gravity;
	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
}
void AI::Gathered()                       //主人のところにいくぞ～～～
{
	search(pl->Getposition());
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
void AI::pasmove(int mokuhyou)
{
	work->kyorikeisan(mokuhyou - 1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe* GameTime().GetFrameDeltaTime());
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
	pasmove(mokuhyou);
	NPCRunangle(work->Getbekutor());
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - this->m_position).Length() < 200.0f) {
		Fardist_path(m_position);
	}
}
void AI::Chasepas(CVector3 m_position)
{
	pasmove(mokuhyou);
	//NPCRunangle(work->Getbekutor());
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - this->m_position).Length() < 200.0f) {
	/*	CVector3 minkore = { FLT_MAX,FLT_MAX,FLT_MAX};
		for (int Linknum = 0; Linknum < game->pasu[Leftfrag].GetresutoSaiz(mokuhyouNo); Linknum++) {
			CVector3 ma = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[Linknum] - m_position;
			if (minkore.Length() > ma.Length()) {
				minkore = ma;
				mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[Linknum];
			}
		}*/
		search(m_position);
		if (jyunban[0] == jyunban[1])
		{
			switch (Leftfrag)		
			{
				case 0:
					destination_Leftfrag = 0;
					Leftfrag = 1;
					search(lam->m_position);
					break;
				case 1:
					destination_Leftfrag = 1;
					Leftfrag = 0;
					search(lam->m_position);
					break;
				default:
					break;
			}
		}
		Retrieval_pasNo(mokuhyou);
	}
}
void AI::NPCescape()//ゾンビから逃げる
{
	CVector3 v = m_position - pl->Getposition();
	v.y = 0.0f;
	float len = v.Length();//長さ
	if (len < 3000.0) {
		hinannpas(pl->Getposition());
	}
	else {
		m_speed = 4.0f;
		mobe = 50.0f; 
		search(game->pasu[Leftfrag].m_pointList[0]);
		Gaizi->Satpoint(0.1);
		work->Setkakudo(5.0f);
		kaiten = false;
		pa = Fade_Out;										//こんな町......もうおさらばだ！！
	}
}
void AI::NPCEscape_NPC()
{
	CVector3 j = this->m_position - lam->m_position;
	if (j.Length() >= 3000) {
		search(retu_position);	//元の位置に、も～～どろ
		pa = Return;
		da = 0;
	}
	else {
		hinannpas(lam->m_position);
		//1人では戦えない！！！//に～げるんだよ～～～～
	}
}
void AI::search(CVector3 mokutekipos)
{
	jyunban.erase(jyunban.begin(), jyunban.end());     //逃げ切ったぜ～～～～
	keiro.tansa(m_position,mokutekipos, &jyunban, Leftfrag);//ゾンビ化NPCが多いときにここでクラッシュ
	escapecaku = 30.0f;
	mokuhyou = jyunban[0];
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