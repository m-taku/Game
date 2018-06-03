#pragma once

#include "kanren.h"
typedef struct {
	CVector3 m_position;
	CVector3 s_position;
	int ime;
	int tunagi;
	std::vector<int> No;
	int cost;
}ando;
		
class keiroK 
{
public:
	keiroK();
	~keiroK();
	int Kans(int count);
	int GetDistance(CVector3 IP,CVector3 GP);
	int BackTrace(int x);
	void tansa(CVector3 i, CVector3 Ta, std::vector<int> *a,int Leftfrag);
	ando stuyt;
	std::vector<ando> open;
	std::vector<ando> close;
	std::vector<kanren> resuto1;
	std::vector<int> jyunban;
private:	
	int f = 1;
	int N = 1;
	int sum = 0;
	int sumd = 0;
	int fghjkl=0;
	CVector3 fa;
	CVector3 ga;
	int No = 0;
};

