#pragma once
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	CVector3 m_position = CVector3::Zero;		//座標。
	CVector3 m_movespeed = CVector3::Zero;		//移動速度。
	CQuaternion qBias_x;
	CQuaternion qBias_z;
	CQuaternion rotation(float a) {
		qBias_x.SetRotationDeg(CVector3::AxisY, 0.0f);
		qBias_z.SetRotationDeg(CVector3::AxisY, a);
		qBias_x.Multiply(qBias_z);
		return qBias_x;
	}
	CVector3 kakudai;
	int Zonbe = 0;//ゾンビ化したときに+1する。

};
extern std::vector<Human*> Humans;

