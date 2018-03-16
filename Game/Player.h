#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
class Player : public Human
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CAnimation m_animation;
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<キャラクタ用のライト。
	CCharacterController m_charaCon;		//キャラクタコントローラ。
	CVector3 m_moveSpeed = CVector3::Zero;
	CShaderResourceView m_normalMap;		//法線マップ。
	CShaderResourceView m_specMap;			//スペキュラマップ。
	CVector3 m_forward;						//プレイヤーの前方。
	float rotY=0.0f; //回転
	CQuaternion qBias;
	CMatrix mRot;
};

