#include "stdafx.h"
#include "kanren.h"


kanren::kanren()
{
}


kanren::~kanren()
{
	int l = No.size();
	for (int i = 0; i < l; i++) {
		auto it = std::find(No.begin(), No.end(), No[0]);
		if (it != No.end()) {
			No.erase(it);
		}
	}
}
void kanren::kanrenz(unsigned int a,std::vector<CVector3> &b)
{
	unsigned int s=a%100000000;
	for (int i = 3; i >= 0; i--)
	{
		unsigned int wa=powf(100.0f, i);
		unsigned int d = s /wa;
		if (d == 0) {
			break;
		}
		m_position.push_back(b[d-1]);
		No.push_back(d);
		s = s %wa;
	}
}
