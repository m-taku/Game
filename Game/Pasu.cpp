#include "stdafx.h"
#include "Pasu.h"
#include"kanren.h"
#include"Game.h"
#include <math.h>


Pasu::Pasu()
{
}


Pasu::~Pasu()
{

}
void Pasu::Load(const wchar_t* filePath,int b)
{
	CSkeleton loc;
	loc.Load(filePath);
	int j = loc.GetNumBones() - 1;
	m_pointList.resize(j);
	No12.resize(j);
	CBone* boan[256];
	for (int i = 1; i < loc.GetNumBones(); i++)
	{
		boan[i] = loc.GetBone(i);
		const CMatrix& mat = boan[i]->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.z = -mat.m[3][1];
		pos.y = mat.m[3][2];
		for (int f = 8; f > 0; f--) {
			int u = 0;
			long long h = 0;
			for (int g = 8; g > f; g--) {
				h += No2[u++] * pow(100, g);
				if (i == 13 && g == 2) {
					if(b ==0)
					h -= 16;
					//int a = 0;
				}
				if (i == 21 && g == 2) {
					if (b == 1)
						h -= 16;
				}
				if (i == 25 && g == 2) {
					if (b == 1)
						h -= 16;
				}
				
			}
			if (h <= 0) {
				No2.push_back(_wtoll(boan[i]->GetName()) / (pow(100, f)));
			}
			else {
				No2.push_back((_wtoll(boan[i]->GetName()) % h) / (pow(100, f)));
			}
			if (No2[u] == 0) {
				break;
			}
		}


		//#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		//		if (No2[i] == 0) {
		//			TK_WARNING_MESSAGE_BOX("パスのノードのボーンの名前が不正です。");
		//			m_pointList.clear();
		//			return;
		//		}
		//#endif
		m_pointList[No2[0] - 1] = pos;
		No12[No2[0] - 1] = No2;
		No2.clear();
	}
	for (int i = 1; i < loc.GetNumBones(); i++)
	{
		kan.kanrenz(No12[i - 1], m_pointList);
		Pasuresuto.push_back(kan);
	}

	for (int l = 0; l < Pasuresuto.size(); l++) {
		if (Pasuresuto[l].No.size()>1)
			resuto.push_back(Pasuresuto[l]);
	}
}