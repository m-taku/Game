#pragma once
class kanren 
{
public:
	kanren();
	~kanren();
	std::vector<CVector3> m_position;
	std::vector<int> No;
	void kanrenz(std::vector<int> &a, std::vector<CVector3> &b);
private:
	int ka = 0;
};

