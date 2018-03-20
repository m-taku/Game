#pragma once
#include "Player.h"
class taieki:public IGameObject
{
public:
	taieki();
	~taieki();
	bool Start();
	void Update();
	void wait();
	void Render(CRenderContext& rc);
	CVector3 tpos = CVector3::Zero;
	CSkinModel m_taieki;
	CSkinModelData m_taiekiModelData;
	int tf = 0;
	CVector3 CF = CVector3::Zero;	//ƒJƒƒ‰‚Ì‘O•ûŒü
	CVector3 TS = CVector3::Zero;
	Player* player = nullptr;
};

