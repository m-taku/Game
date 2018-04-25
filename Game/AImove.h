#pragma once
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start() override;
	void kyorikeisan(int bangou);
	//CSkinModel m_skinModel;					//スキンモデル。
	//CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CVector3 bekutor=CVector3::Zero;
	Game* game;
	CVector3 K;
	int g = 0;
};

