#pragma once
#include"Game.h"
class AImove : public IGameObject
{
public:
	AImove();
	~AImove();
	//(行きたいパスの番号,自分の位置,前方向)
	int kyorikeisan(int bangou, CVector3 m_pos, CVector3 m_forward, std::vector<CVector3> pasu);
	//(行きたい場所,自分の位置,前方向)
	int kyorikeisan(CVector3 mokuteki , CVector3 m_pos, CVector3 m_forward);
	//動く速さ取得
	float Getmuve() const
	{
		return muve;
	}
	//目的地取得
	CVector3 Getmokuteki() const
	{
		return mokuteki;
	}
	//回転行列取得
	CQuaternion Getkaku() const
	{
		return qBias1;
	}
	//回転しているかどうか（0：回転していない、それ以外：回転した）
	float Getkaiten() const
	{
		return kaku;
	}
	//回転させたい角度（1フレーム当たり）
	void Setkakudo(float kku) 
	{
		kakudo = kku;
	}
	//目的地までの距離
	float Getlen() const
	{
		return len;
	}
	//目的地との角度の誤差替え
	void Sethaba(float kakudo) 
	{
		haba = kakudo;
	}
private:
	CQuaternion qBias1 = CQuaternion::Identity; //回転行列
	float muve = 1.0;								//速さ
	float len = 0.0;							//目的地までのの距離
	CVector3 bekutor=CVector3::Zero;			
	Game* game;									
	CVector3 mokuteki = CVector3::Zero;			//目的地の座標
	float kaku = 0.0f;							//回転角度
	float haba = 3.0f;							//目的地の角度のごさ
	float kakudo = 3.0f;						//曲げる角度
};

