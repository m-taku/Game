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
void kanren::kanrenz(std::vector<int> &a, std::vector<CVector3> &b)
{
	m_position.clear();
	No.clear();
	for (int i = 0; i < a.size(); i++) {
		if (a[i] != 0) {
			m_position.push_back(b[a[i] - 1]);
			No.push_back(a[i]);
		}
	}
	//隣接ノードへの移動コストを計算する。
	moveCosts.resize(m_position.size());
	moveCosts[0] = 0.0f;
	for (int i = 1; i < m_position.size(); i++) {
		auto vDist = m_position[0] - m_position[i];
		moveCosts[i] = vDist.Length();
	}
}
