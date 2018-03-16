#pragma once

#include "Player.h"
class camera:public IGameObject
{
public:
	camera();
	~camera();
	bool Start();
	void Update();

	/////////////////////////////////////
	//メンバ変数
	/////////////////////////////////////
	Player* m_player;	//プレイヤー。
	CVector3 target;
	CVector3 Ppos;
};

