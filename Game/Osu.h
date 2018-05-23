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

};

