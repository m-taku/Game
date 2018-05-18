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

