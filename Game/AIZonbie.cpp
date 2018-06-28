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
void AI::NPCZombie_Normal()
{
	//	work->kyorikeisan(mokuhyou-1, m_position, m_forward, game->pasu[Leftfrag].m_pointList);
	//	m_rotation.Multiply(work->Getkaku());//回転
	//	m_movespeed = m_forward * (work->Getmuve()*m_speed + mobe);
	//	m_movespeed.y += gravity;
	//	m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動
	pasmove(mokuhyou);
	m_rotation.Multiply(work->Getkaku());//回転
	if ((game->pasu[Leftfrag].Getresuto(mokuhyouNo)->m_position[0] - m_position).Length() < 150.0f) {//ランダム徘徊のパス番号検索
		int num = Random().GetRandInt() % (game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No.size() - 1);
		mokuhyou = game->pasu[Leftfrag].Getresuto(mokuhyouNo)->No[++num];
		Retrieval_pasNo(mokuhyou);
	}
	if (Tansaku != nullptr) {
		search(Tansaku->m_position);
		mokuhyou = jyunban[0];
		Retrieval_pasNo(mokuhyou);
		pa = Zombie_Chase; //パターンをゾンビチェイスに変える。
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
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len > 2100.0f || Tansaku->Raifu_f == true) {//他のNPCを見失った(距離が2100以上あいた)、あるいは死んだら				
		Tansaku = nullptr; //検索結果を初期化する。
		kaiten = false;
		angle = 0;
		HitFlag = false;
		nearestpas();
		pa = Zombie_Normal;
	}
	else {//NPCを見失っておらず、見つけていたら
		CVector3 n = m_position - Tansaku->m_position;
		float kou = VectorAngleDeg((Tansaku->m_forward), n);
		n.Normalize();
		if (len >= 1300.0f)
		{
			Chasepas(Tansaku->m_position);//経路たんさ？
			m_rotation.Multiply(work->Getkaku());
		}
		else if (len < atakkukyori) {//NPCに追いついたら
									//攻撃する(確実に当たる仕様)。
			HitFlag = true;//「NPCに攻撃を当てた」というフラグをたてる。
			if (Tansaku->muteki_Flag == false) {
				Tansaku->NPCHP -= 40.0f;
			}
			atakkukyori = 300.0f;
			//NPC_Attack_Animation();//攻撃アニメーションを流す。
		}
		else {
			if (kou >= 120) {
				HitFlag = false;
				n = Tansaku->m_position - m_position;
				n.y = 0.0f;
				n.Normalize();
				NPCRunangle(n);
				m_movespeed = n * (m_speed*200.0 + mobe);
				m_movespeed.y += gravity;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動

				//Chasepas(Tansaku->m_position);
				atakkukyori = 200.0f;
				/////////////////////////////////
				//市民NPCを追跡する処理。
				/////////////////////////////////
			}
			else {
				Pboneforward = Tansaku->m_forward; 
				Pboneforward.y = 0.0f;
				n.y = 0.0f;
				n.Normalize();
				CVector3 rotAxis;
				rotAxis.Cross(n, Pboneforward);
				rotAxis.Normalize(); 
				if (rotAxis.y < 0.0f) {
					rotAxis = CVector3::AxisY;
					rotAxis.y = -1.0f;
				}
				else {
					rotAxis = CVector3::AxisY;
				}
				angle = 10.0f;
				Crot.SetRotationDeg(rotAxis, angle);
				Crot.Multiply(n);
				CVector3 Destination = (n * len) + Tansaku->m_position;
				Destination = m_position - Destination;
				Destination.y = 0.0f;
				NPCRunangle(Destination);
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), Destination);

				/*	Pboneforward = Tansaku->m_forward;
				CVector3 rotAxis;
				rotAxis.Cross(this->m_forward, Pboneforward);
				rotAxis.Normalize();
				angle += 3.0f;
				Crot.SetRotationDeg(rotAxis, angle);
				Crot.Multiply(Pboneforward);
				CVector3 baka = (Pboneforward * len) + Tansaku->m_position;
				baka = baka - m_position;
				m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), baka);*/
			}
		}

	}
}
void AI::NPCZombie_Attack()//vs特殊部隊
{
	static int flame = 40;
	if (tekip != NULL) {
		float len = GetKyori(m_position, tekip->tamapos[No]);
		if (len > 2100.0f &&tekip->tekiheiflag[No] <= 0) {//他のNPCを見失った(距離が2100以上あいた)、あるいは死んだら							  
			kaiten = false;  //元の位置に戻る。
			HitFlag = false;// //検索結果を初期化する。
			escapecaku = 30.0f;
			nearestpas();
		}
		else {//NPCを見失っておらず、見つけていたら
			kannkaku = true;
			CVector3 n = tekip->tamapos[No] - m_position;
			NPCRunangle(n);
			if (len < atakkukyori) {//NPCに追いついたら
									//攻撃する(確実に当たる仕様)。
				HitFlag = true;//「NPCに攻撃を当てた」というフラグをたてる。
				if (flame >= 40) {
					tekip->tekiHP[No] -= 3;
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
	}

}