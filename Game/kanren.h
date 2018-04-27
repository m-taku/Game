#pragma once
class kanren : public IGameObject
{
public:
	kanren();
	~kanren();
	void kanrenz(unsigned int a, std::vector<CVector3> &b);
	std::vector<CVector3> m_position;
	std::vector<int> No;
private:
	int ka = 0;
};

