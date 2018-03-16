#pragma once
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	CVector3 m_position = { 0.0f,0.0f,0.0f };		//座標。
	CVector3 m_movespeed = { 0.0f,0.0f,0.0f };		//移動速度。
	CQuaternion qBias_x;
	CQuaternion qBias_z;
	CQuaternion rotation(int a) {
		qBias_x.SetRotationDeg(CVector3::AxisY, 90.0f);
		qBias_z.SetRotationDeg(CVector3::AxisY, a);
		qBias_x.Multiply(qBias_z);
		return qBias_x;
	}
	void Muve(CVector3 X) {
		m_position += X;
		//return m_position;
	}
	CVector3 kakudai;
	int Zonbe = 0;
};

