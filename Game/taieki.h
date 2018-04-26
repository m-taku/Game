#pragma once
#include "Player.h"
#include "tekihei.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class taieki:public IGameObject
{
public:
	taieki();
	~taieki();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CVector3 tpos = CVector3::Zero;
	CSkinModel m_taieki;
	CSkinModelData m_taiekiModelData;
	int tf = 0;
	CVector3 PS = CVector3::Zero;
	CVector3 CF = CVector3::Zero;	//ƒJƒƒ‰‚Ì‘O•ûŒü
	CVector3 TS = CVector3::Zero;
	Player* player = nullptr;
	tekihei* tekip = nullptr;
	CVector3 e_pos = CVector3::Zero;
	CVector3 taieki_to_tekipos[teki];
	CVector3 tekipos2[teki];
	float tekikyori[teki];
	prefab::CEffect* effect = nullptr;
};

