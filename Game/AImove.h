#pragma once
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	bool Start();
	//(行きたいパスの番号,自分の位置,前方向)
	int kyorikeisan(int bangou, CVector3 m_pos, CVector3 m_forward);
	//動く速さ取得
	int Gatmuve() const
	{
		return muve;
	}
	//目的地取得
	CVector3 Gatmokuteki() const
	{
		return mokuteki;
	}
	//回転角度取得
	CQuaternion Gatkaku() const
	{
		return qBias1;
	}
	float Gatlen() const
	{
		return len;
	}
private:
	CQuaternion qBias1= CQuaternion::Identity;
	int muve = 0;
	float len = 0.0;
	CVector3 bekutor=CVector3::Zero;
	Game* game;
	CVector3 mokuteki = CVector3::Zero;
};

