#pragma once
#include"Player.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 5
class tekihei : public IGameObject
{
public:
	tekihei();
	~tekihei();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);

	CSkinModel tekiskinModel[teki];					//スキンモデル。
	CSkinModelData tekiskinModelData[teki];
	CCharacterController m_charaCon[teki];		//キャラクタコントローラ。
	CVector3 tekipos[teki];
	CVector3 tekispeed[teki];
	CQuaternion tekirot[teki];
	CMatrix m_tekirot[teki];
	CVector3 tekiright[teki];
	Player *Pp = nullptr;
	CVector3 ppos = CVector3::Zero;
	CVector3 teki_to_player[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];

};