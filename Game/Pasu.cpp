#include "stdafx.h"
#include "Pasu.h"
#include"kanren.h"


Pasu::Pasu()
{
}


Pasu::~Pasu()
{

}
void Pasu::Load(const wchar_t* filePath)
{
	CSkeleton loc;
	loc.Load(filePath);
	int j = loc.GetNumBones() - 1;
	m_pointList.resize(j);
	CBone* boan[256];
	pointNo.resize(j);
	for (int i = 1; i < loc.GetNumBones(); i++)
	{
		boan[i] = loc.GetBone(i);
		const CMatrix& mat = boan[i]->GetBindPoseMatrix();
		CVector3 pos;
		pos.x = mat.m[3][0];
		pos.z = -mat.m[3][1];
		pos.y = mat.m[3][2];
		unsigned int No2 = _wtoll(boan[i]->GetName());
#if BUILD_LEVEL != BUILD_LEVEL_MASTER
		if (No2 == 0) {
			TK_WARNING_MESSAGE_BOX("パスのノードのボーンの名前が不正です。");
			m_pointList.clear();
			return;
		}
#endif
		unsigned int No = No2 / 100000000;
		m_pointList[No - 1] = pos;
		pointNo[No - 1] = No2;
	}
	for (int i = 0; i < loc.GetNumBones()-1; i++) {
		kan = NewGO<kanren>(0);
		kan->kanrenz(pointNo[i],m_pointList);
		resuto.push_back(kan);
	}
}

