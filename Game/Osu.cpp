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
	m_skinModelData.Load(L"modelData/liam.cmo");//男性型を書け
	m_skinModel.Init(m_skinModelData);
	ai_NPCAnimationClips[shiminidle].Load(L"animData/shiminidle.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminidle].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminwalk].Load(L"animData/shiminwalk.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminrun].Load(L"animData/shiminrun.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminrun].SetLoopFlag(true);
	ai_NPCAnimationClips[shiminattack].Load(L"animData/playerattack.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[shiminattack].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiwalk].Load(L"animData/playerwalk.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[Zonbiwalk].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbiattack].Load(L"animData/playerattack.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[Zonbiattack].SetLoopFlag(true);
	ai_NPCAnimationClips[Zonbi_zico].Load(L"animData/liam_ziko.tka");//仮。後で入れろ。
	ai_NPCAnimationClips[Zonbi_zico].SetLoopFlag(false);
	
	//アニメーションの初期化。
	ai_NPCAnimation.Init(
		m_skinModel,			//アニメーションを流すスキンモデル。
									//これでアニメーションとスキンモデルが関連付けされる。
		ai_NPCAnimationClips,	//アニメーションクリップの配列。

		animnum					//アニメーションクリップの数。
	);
	zondi.CreateFromDDSTextureFromFile(L"modelData/LiamTexZonbi1.dds");
	m_skinModel.FindMaterial([&](CModelEffect* material) {
	material->Setm_zonbi(zondi.GetBody());
	});
	AI::Start();

	return true;
}

//NPCゾンビに抵抗しているときの処理。AIクラスの同じメソッド(メンバ関数)をオーバーライドする。
//void Osu::NPCResistance_NPC() 
//{
//	pa = Damage;
//}

//プレイヤーゾンビに抵抗しているときの処理。AIクラスの同じメソッド(メンバ関数)をオーバーライドする。
//void Osu::NPCResistance_Player()
//{
//	static int count = 30;//初期値。
//	static int i = 0;//毎フレームカウントする。
//
//	i++;//毎フレーム実行。
//	
//	//Resistance_Animation();
//		
//		if (i > 7) {//8フレーム以上で作動する。
//			count++;
//			i = 0;
//		}
//
//		if (Pad(0).IsTrigger(enButtonB)) { //Bボタンが押されたら
//			count--;
//		}
//
//		if (count <= 0) {//countが0以下になったら
//			count = 30;//値を初期化。
//			i = 0;//フレームカウントの値を初期化。
//			pa = Damage;//パターンをダメージに変える。
//		}
//
//		if (count >= 60) {//countが60以上になったら
//			count = 30;//値を初期化。
//			i = 0;//フレームカウントの値を初期化。
//		//	muteki_Flag = true;//無敵フラグをあげて、無敵化する。
//			pa = Return;//パターンをリターンに変える。
//		}
//	
//}

void Osu::Update()
{

	AI::Update();
	AI_Animation();
}
void Osu::AI_Animation()//AIのアニメーション制御
{
	/*if (m_speed <= 1.0) {
	Loop_Walk_Animation();
	}
	if (m_speed > 1.0) {
	Loop_Run_Animation();
	}*/
	if (GetZonbi() == false) {
		if (HitFlag == true)
		{
			NPC_Attack_Animation();

		}
		else if (m_speed < 0.5f) {
			Idle_Animation();
		}
		else if (m_speed <= 1.0) {
			Loop_Walk_Animation();
		}
		else if (m_speed > 1.0) {
			Loop_Run_Animation();
		}

	}
	else {
		if (pa == flyNPC) {
			Zombie_Ziko_Animation();
		}
		else if (HitFlag == true) {
			NPC_Attack_Animation();
		}
		else if (m_speed >= 0.5f) {
			Zombie_Walk_Animation();
		}
	}
}
void Osu::Idle_Animation() //キャラクターが歩き続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminidle, 0.7);
}


void Osu::Loop_Walk_Animation()//キャラクターが歩き続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminwalk, 0.7);
}
void Osu::Loop_Run_Animation()//キャラクターが走り続ける時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminrun, 0.7);
}

void Osu::NPC_Attack_Animation()//ゾンビ化キャラクターが攻撃している時のアニメーションの処理。
{
	ai_NPCAnimation.Play(shiminattack, 0.2);
}


void Osu::Zombie_Walk_Animation()
{
	ai_NPCAnimation.Play(Zonbiwalk, 0.7);
}
void Osu::Zombie_Ziko_Animation()
{
	ai_NPCAnimation.Play(Zonbi_zico, 0.7);
	if (!ai_NPCAnimation.IsPlaying()) {
		pa = Zombie_Normal;
	}
}
