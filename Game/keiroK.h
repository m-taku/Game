#pragma once

#include "kanren.h"
typedef struct {
	CVector3 m_position;
	CVector3 s_position;
	int ime;
	std::vector<int> No;
	int cost;
	int beforeNo;
}ando;
		
class keiroK 
{
public:
	keiroK();
	~keiroK();
	int Kans(int currentCost);
	void tansa(CVector3 i, CVector3 Ta, std::vector<int> *a,int Leftfrag);
	
	std::vector<int> jyunban;
private:	
};

