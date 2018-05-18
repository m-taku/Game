#include "stdafx.h"
#include "Mes.h"


Mes::Mes()
{
}


Mes::~Mes()
{
}


bool Mes::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//女性型を書け
	m_skinModel.Init(m_skinModelData);
	AI::Start();

	return true;
}

void Mes::NPCNormal_Search()
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//長さ
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.1);
		pa = Escape;
	}
}


void Mes::Start_Walk_Animation()//キャラクターが歩き始める時のアニメーションの処理。
{

}

void Mes::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
{

}

void Mes::Start_Run_Animation()//キャラクターが走り始める時のアニメーションの処理。
{

}

void Mes::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
{

}

void Mes::Resistance_Animation()//キャラクターが抵抗している時のアニメーションの処理。
{

}

void Mes::Zombie_Attack_Animation()//ゾンビ化キャラクターが攻撃しているのアニメーションの処理。
{

}
