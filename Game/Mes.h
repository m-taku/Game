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
};

