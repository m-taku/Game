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
	//tkaファイルの読み込み。6種類。
	//ai_NPCAnimationClips[0].Load(L"Assets/animData/walk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[0].SetLoopFlag(true);

	//ai_NPCAnimationClips[1].Load(L"Assets/animData/walk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[1].SetLoopFlag(true);

	//ai_NPCAnimationClips[2].Load(L"Assets/animData/walk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[2].SetLoopFlag(true);

	//ai_NPCAnimationClips[3].Load(L"Assets/animData/walk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[3].SetLoopFlag(true);

	//ai_NPCAnimationClips[4].Load(L"Assets/animData/walk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[4].SetLoopFlag(true);

	//ai_NPCAnimationClips[5].Load(L"Assets/animData/walk.tka");//仮。後で入れろ。
	//ai_NPCAnimationClips[5].SetLoopFlag(true);

	AI::Start();

	return true;
}

