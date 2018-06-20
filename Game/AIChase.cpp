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
		search(retu_position);
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
			Chasepas(lam->m_position);
			HitFlag = false;
			furag = 0;
			m_speed = 4.0f;
			//mokuteki.y = 0.0f;
			//mokuteki.Normalize();//正規化して向きベクトルにする。
			//m_movespeed = mokuteki * (150 * m_speed + mobe);
			//m_movespeed.y += gravity;
			//m_position = A_charaCon.Execute(GameTime().GetFrameDeltaTime(), m_movespeed);
			atakkukyori = 100.0f;
		}
	}
}

