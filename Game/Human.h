#pragma once
class Human : public IGameObject
{
public:
	Human();
	~Human();
	bool Start();
	void Update();
	void Setposition(CVector3 position)
	{
		H_position = position;
	}
	CVector3 Getposition()
	{
		return H_position;
	}
	void SetZonbe()
	{
		Zonbe =true;
	}
	bool GetZonbi()
	{
		return Zonbe;
	}
private:
	CVector3 H_position = CVector3::Zero;		//座標。
	CVector3 kakudai;
	bool Zonbe =false;//ゾンビ化したときに+1する。
};
extern std::vector<Human*> Humans;

