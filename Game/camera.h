#pragma once
#include "Player.h"
#include"tkEngine\graphics\tkSkeleton.h"
class camera:public IGameObject
{
public:
	camera();
	~camera();
	bool Start();
	void Update();

	/////////////////////////////////////
	//ÉÅÉìÉoïœêî
	/////////////////////////////////////
	
	CVector3 target = CVector3::Zero;
	CVector3 Ppos = CVector3::Zero;
	float d = 0.0f;
	CVector3 position_of_player;
	Player* m_player = nullptr;
	CSkeleton playerS;
	float cameradeg = 0.0f;
	CQuaternion Crot = CQuaternion::Identity;
	CVector3 Pboneforward = CVector3::Zero;

};

