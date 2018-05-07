#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
class taieki;
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
	CVector3 m_rite;						//プレイヤーの右方向
	float rotY = 0.0f; //回転
	float rotX = 0.0f; //回転
	CQuaternion qBias;
	CQuaternion qBias1;
	CQuaternion qrot;
	CMatrix mRot;
	CQuaternion m_rotation = CQuaternion::Identity;//キャラの回転
	CQuaternion d_rotation = CQuaternion::Identity;//ダミーの回転（縦）
	CSkinModel m_taieki;
	CSkinModelData m_taiekiModelData;
	taieki* Tp = nullptr;
	prefab::CEffect* hakaba = nullptr;
	CVector3 landpos = CVector3::Zero;
	CVector3 land_to_player = CVector3::Zero;
	float land_to_player_vector = 0.0f;
	int landflag = 1;

};

