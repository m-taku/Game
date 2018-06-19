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
	m_skinModelData.Load(L"modelData/SimpleCorgi.cmo");//犬を書け
	m_skinModel.Init(m_skinModelData);
	m_speed = 1.5f; //ノーマル状態のときの移動速度。
	//tkaファイルの読み込み。6種類。
	//ai_NPCAnimationClips[waon].Load(L"animData/waon.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[waon].SetLoopFlag(true);

	//ai_NPCAnimation.Init(
	//	m_skinModel,			//アニメーションを流すスキンモデル。
	//							//これでアニメーションとスキンモデルが関連付けされる。
	//	ai_NPCAnimationClips,	//アニメーションクリップの配列。

	//	animnum					//アニメーションクリップの数。
	//);
	AI::Start();

	return true;
}

