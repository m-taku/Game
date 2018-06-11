#include "stdafx.h"
#include"Game.h"
#include "AIMove.h"
#include "Osu.h"



Osu::Osu()
{
}


Osu::~Osu()
{
}

bool Osu::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//男性型を書け
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

//NPCゾンビに抵抗しているときの処理。AIクラスの同じメソッド(メンバ関数)をオーバーライドする。
void Osu::NPCResistance_NPC() 
{
	pa = Damage;
}

//プレイヤーゾンビに抵抗しているときの処理。AIクラスの同じメソッド(メンバ関数)をオーバーライドする。
void Osu::NPCResistance_Player()
{
	static int count = 30;//初期値。
	static int i = 0;//毎フレームカウントする。

	i++;//毎フレーム実行。
	
	//Resistance_Animation();
		
		if (i > 7) {//8フレーム以上で作動する。
			count++;
			i = 0;
		}

		if (Pad(0).IsTrigger(enButtonB)) { //Bボタンが押されたら
			count--;
		}

		if (count <= 0) {//countが0以下になったら
			count = 30;//値を初期化。
			i = 0;//フレームカウントの値を初期化。
			pa = Damage;//パターンをダメージに変える。
		}

		if (count >= 60) {//countが60以上になったら
			count = 30;//値を初期化。
			i = 0;//フレームカウントの値を初期化。
		//	muteki_Flag = true;//無敵フラグをあげて、無敵化する。
			pa = Return;//パターンをリターンに変える。
		}
	
}


