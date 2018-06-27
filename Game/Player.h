#pragma once
#include"Human.h"
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include"tkEngine/sound/tkSoundSource.h"
#define tama 20
class taieki;
class car;
class Player : public Human
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	CVector3 GetPosition()
	{
		return m_position;
	}
	CVector3& Getboneforward()
	{
		return boneforward;
	}

	CVector3& Getbonepos()
	{
		return bonepos;
	}
	void trueGame()
	{
		game = true;
	}
	void falseGame()
	{
		game = false;

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

	void Play_Respiration(CVector3 m_moveDecision);//息遣いの音を再生させるかを判断する。

	bool CVector_same_Decision(CVector3 a, CVector3 b);//二つのベクトルが同一なのかを調べる。
	
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
	CVector3 m_moveDecision = CVector3::Zero;//動いているのかを判定する。
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
	taieki* Tp[20];
	int taieki_sum = 0;
	float taieki_timer = 0;
	int taieki_F = 0;
	prefab::CEffect* hakaba = nullptr;
	CVector3 landpos = CVector3::Zero;
	CVector3 land_to_player = CVector3::Zero;
	float land_to_player_vector = 0.0f;
	int landflag = 1;
	wchar_t bonename[50];
	int bonenum = 0;
	int boneNo = 0;
	CVector3 bonepos = CVector3::Zero;
	bool zikofrag = false;
	enum animation {
		idle,
		walk,
		attack,
		ziko,
		animnum
	};
	car* carpoint;
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
	float muteki_count = 0;//無敵時間のカウント。
	bool  muteki_Flag = false;
	bool collision_f = false;
	float blend = 0.0f;
	//CVector3 m_moveSpeed_log = CVector3::Zero;//moveSpeedを保持する。
	bool X_button_Flag = false;//Xボタンが押されたかどうかを保持するフラグ。
	prefab::CSoundSource*m_Respiration = nullptr;//息使いの音。歩くときに流す。
};

