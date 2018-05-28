#pragma once
#include"AImove.h"
class car : public IGameObject
{
public:
	car();
	~car();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
private:
	void Move();
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	AImove* ran;
	CQuaternion m_rotation = CQuaternion::Identity;		//回転
	CVector3 m_position = CVector3::Zero;				//現在の座標
	CMatrix m_tekirot;									//行列
	CVector3 m_forward;									//キャラの前方。
	float  move = 1.0f;									//移動速度（倍率、1.0が普通）
	std::vector<CVector3> No;
	float speed = 1000;									//常に走るスピード
	std::vector<int>::iterator pasu;
	int saidaiNo = 0;
	int ima = 0;
	void Stop();
	int fa = 0;
	int frag = 0;
};

