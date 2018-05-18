#pragma once
#include"AI.h"
#include"Game.h"
/*NPCの男性型クラス(AIクラスから継承)。

*/
class Osu: public AI
{
public:
	Osu();
	~Osu();
	bool Start();
	void NPCResistance_NPC();  //NPCゾンビに抵抗しているときの処理。
	void NPCResistance_Player();  //プレイヤーゾンビに抵抗しているときの処理。

	void Start_Walk_Animation();//歩き始めの処理。
	void Loop_Walk_Animation();//歩き続けるときの処理。
	void Start_Run_Animation();//走り始めの処理。
	void Loop_Run_Animation();//走り続けるときの処理。
	void Resistance_Animation();//抵抗しているときの処理。
	void Zombie_Attack_Animation();//ゾンビ化NPCが攻撃するときの処理。
};

