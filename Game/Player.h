#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#define tama 20
class taieki;
class Player : public Human
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CVector3& GetPosition()
	{
		return Getposition();
	}
	CVector3& Getboneforward()
	{
		return boneforward;
	}

	CVector3& Getbonepos()
	{
		return bonepos;
	}
	void SetGame()
	{
		game = true;
	}
	CVector3& GetFoeward()
	{
		return m_forward;
	}

	CVector3& Getboneright()
	{
		return boneright;
	}

	CVector3& Getboneup()
	{
		return boneup;
	}

	CVector3 &GetMoveSpeed()
	{
		return m_moveSpeed;
	}
	int GetattackF()
	{
		return attackF;
	}
	
private:
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	prefab::CDirectionLight* m_charaLight = nullptr;	//!<キャラクタ用のライト。
	CCharacterController m_charaCon;
	CShaderResourceView m_normalMap;		//法線マップ。
	CShaderResourceView m_specMap;
			//キャラクタコントローラ。
	CVector3 m_moveSpeed = CVector3::Zero;
	CVector3 m_position = CVector3::Zero;
				//スペキュラマップ。
	CVector3 m_forward=CVector3::Zero;						//プレイヤーの前方。
	CVector3 m_rite= CVector3::Zero;						//プレイヤーの右方向
	float rotY = 0.0f; //回転
	float rotX = 0.0f; //回転
	CQuaternion qBias=CQuaternion::Identity;
	CQuaternion qBias1 = CQuaternion::Identity;
	CQuaternion qrot = CQuaternion::Identity;
	CMatrix mRot;
	CQuaternion m_rotation = CQuaternion::Identity;//キャラの回転
	CQuaternion d_rotation = CQuaternion::Identity;//ダミーの回転（縦）
	//CSkinModel m_taieki;
	//CSkinModelData m_taiekiModelData;
	taieki* Tp = nullptr;
	prefab::CEffect* hakaba = nullptr;
	CVector3 landpos = CVector3::Zero;
	CVector3 land_to_player = CVector3::Zero;
	float land_to_player_vector = 0.0f;
	int landflag = 1;
	wchar_t bonename[50];
	int bonenum = 0;
	int boneNo = 0;
	CVector3 bonepos = CVector3::Zero;
	
	enum animation {
		idle,
		walk,
		attack,
		attack2,
		animnum
	};
	CAnimation m_animation;
	CShaderResourceView zondi;
	CAnimationClip m_animclip[animnum];
	int attackF = 0;
	int attackcounter = 0;
	CQuaternion bonerot = CQuaternion::Identity;
	CVector3 boneforward = CVector3::Zero;
	CVector3 boneright = CVector3::Zero;
	CVector3 boneup = CVector3::Zero;
	CMatrix bonerot_M;
	bool game = false;
	//////////T.M////////////////////////////
	float Log_lStick_x = 0.0f;
	float Log_lStick_y = 0.0f;
	//CVector3 m_moveSpeed_log = CVector3::Zero;//moveSpeedを保持する。
	bool X_button_Flag = false;//Xボタンが押されたかどうかを保持するフラグ。
};

