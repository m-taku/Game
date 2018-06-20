#pragma once
#include"tekihei.h"
#define tekikazu 10
class item : public IGameObject
{
public:
	item();
	~item();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel itemModel[tekikazu];					//スキンモデル。
	CSkinModelData itemModelData;			//スキンモデルデータ。
	CVector3 itempos[tekikazu];
	CQuaternion itemrot[tekikazu];
	int itemf[tekikazu];
	tekihei *tp;
	
};

