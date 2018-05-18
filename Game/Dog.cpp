#include "stdafx.h"
#include "Dog.h"


Dog::Dog()
{
}


Dog::~Dog()
{
}

bool Dog::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//犬を書け
	m_skinModel.Init(m_skinModelData);
	m_speed = 800.0f; //ノーマル状態のときの移動速度。
	AI::Start();

	return true;
}


void Dog::Start_Walk_Animation()//キャラクターが歩き始める時のアニメーションの処理。
{

}

void Dog::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
{

}

void Dog::Start_Run_Animation()//キャラクターが走り始める時のアニメーションの処理。
{

}

void Dog::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
{

}

void Dog::Resistance_Animation()//キャラクターが抵抗している時のアニメーションの処理。
{

}

void Dog::Zombie_Attack_Animation()//ゾンビ化キャラクターが攻撃しているのアニメーションの処理。
{

}

