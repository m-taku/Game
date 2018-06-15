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
void AI::NPCChase()
{
	CVector3 mokuteki = lam->m_position - m_position;
	NPCRunangle(mokuteki);
	if (lam->Raifu_f == true) {
		pa = Return;
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
		escapecaku = 30.0f;
		Chasefrag = 0;
		m_speed = 1.0f;
		lam = nullptr;
		HitFlag = false;
	}
	else {
		if (mokuteki.Length() <= atakkukyori) {
			m_speed = 0.0f;
			HitFlag = true;
			if (lam->muteki_Flag == false) {
				lam->NPCHP -= 20.0f;
			}
			atakkukyori = 200.0f;
		}
		else {
			HitFlag = false;
			furag = 0;
			m_speed = 4.0f;
			mokuteki.y = 0.0f;
			mokuteki.Normalize();//正規化して向きベクトルにする。
			m_movespeed = mokuteki * (150 * m_speed + mobe);
			m_movespeed.y += gravity;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
			atakkukyori = 100.0f;
		}
	}
}
void AI::NPCZombie_Chase()
{
	float len = GetKyori(m_position, Tansaku->m_position);
	if (len > 2100.0f || Tansaku->Raifu_f == true) {//他のNPCを見失った(距離が2100以上あいた)、あるいは死んだら
													//元の位置に戻る。
		jyunban.erase(jyunban.begin(), jyunban.end());
		keiro.tansa(m_position, retu_position, &jyunban, Leftfrag);
		Tansaku = nullptr; //検索結果を初期化する。
		kaiten = false;
		angle = 0;
		HitFlag = false;
		escapecaku = 30.0f;
		nearestpas();
		pa = Zombie_Normal;
	}
	else {//NPCを見失っておらず、見つけていたら
		float kou = VectorAngleDeg((Tansaku->m_forward));
		CVector3 n = Tansaku->m_position - m_position;
		NPCRunangle(n);
		if (kou <= 120) {
			if (len < atakkukyori) {//NPCに追いついたら
									//攻撃する(確実に当たる仕様)。
				HitFlag = true;//「NPCに攻撃を当てた」というフラグをたてる。
				if (Tansaku->muteki_Flag == false) {
					Tansaku->NPCHP -= 40.0f;
				}

				atakkukyori = 200.0f;
				//NPC_Attack_Animation();//攻撃アニメーションを流す。
			}
			else {
				HitFlag = false;
				//n.y = 0.0f;
				//n.Normalize();
				//m_movespeed = n * (m_speed*200.0 + mobe);
				//m_movespeed.y += gravity;
				//m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);//移動

				atakkukyori = 100.0f;
				/////////////////////////////////
				//市民NPCを追跡する処理。
				/////////////////////////////////
			}
		}
		else {
			Pboneforward = Tansaku->m_forward;
			CVector3 rotAxis;
			rotAxis.Cross(this->m_forward, Pboneforward);
			rotAxis.Normalize();
			angle += 3.0f;
			Crot.SetRotationDeg(rotAxis, angle);
			Crot.Multiply(Pboneforward);
			CVector3 baka = (Pboneforward * len) + Tansaku->m_position;
			baka = baka - m_position;
			m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), baka);
		}
	}
}
void AI::Idle_Animation() //キャラクターが歩き続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminidle, 0.7);
}


void AI::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminwalk, 0.7);
}


void AI::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminrun, 0.7);
}

void AI::Zombie_Walk_Animation()
{
	ai_NPCAnimation.Play(Zonbiwalk, 0.7);
}
