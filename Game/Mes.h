#pragma once
#include"AI.h"
/*NPCの女性型クラス(AIクラスから継承)。

*/
class Mes: public AI
{
public:
	Mes();
	~Mes();
	bool Start();

	void NPCNormal_Search();//女性型の警戒処理。

	void Start_Walk_Animation();//歩き始めの処理。
	void Loop_Walk_Animation();//歩き続けるときの処理。
	void Start_Run_Animation();//走り始めの処理。
	void Loop_Run_Animation();//走り続けるときの処理。
	void Resistance_Animation();//抵抗しているときの処理。
	void Zombie_Attack_Animation();//ゾンビ化NPCが攻撃するときの処理。
};

