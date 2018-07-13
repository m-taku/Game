#pragma once
#include"AI.h"
#include"Game.h"
/*NPCの男性型クラス(AIクラスから継承)。

*/
class Osu : public AI
{
public:
	Osu();
	~Osu();
	bool Start();
	void AI_Animation();//AIのアニメーションの移行を処理する。
	void Update();
	//void NPCResistance_NPC();  //NPCゾンビに抵抗しているときの処理。
	//void NPCResistance_Player();  //プレイヤーゾンビに抵抗しているときの処理。
	void death_Animation();
	void Idle_Animation();

	void Loop_Walk_Animation();//歩き続けるときの処理。

	void Loop_Run_Animation();//走り続けるときの処理。

	void Zombie_Walk_Animation();//ゾンビ化NPCが歩き続けるときの処理。
								 //void Resistance_Animation();//抵抗しているときの処理。
	void NPC_Attack_Animation();//ゾンビ化NPCが攻撃するときの処理。
	void Zombie_Ziko_Animation();
private:

	enum animation {
		shiminidle,
		shiminwalk,
		shiminrun,
		shiminattack,
		shimindeath,
		shiminkai,
		shiminoki,
		Zonbiwalk,
		Zonbiattack,
		Zonbi_zico,
		animnum
	};
	bool okiagari = false;
	CAnimation ai_NPCAnimation;				//アニメーション。
	CAnimationClip ai_NPCAnimationClips[animnum];	//アニメーションクリップ。
	static CShaderResourceView* zondi ;
};

