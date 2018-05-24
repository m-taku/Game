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

void Mes::NPCNormal_Search()
{
	CVector3 v2 = pl->m_position - m_position;
	float len1 = v2.Length();//長さ
	if (Siya(v2, len1) != 0) {
		Gaizi->Satpoint(0.3);//見つかった時のペナルティが通常の3倍。シャア
		pa = Escape;
	}
}
