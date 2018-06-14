#pragma once
#include"Player.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 40
#define path 45
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
	CVector3 tekipos[teki];//敵のポジション
	CVector3 tekispeed[teki];//移動速度
	CQuaternion tekirot[teki];
	CMatrix m_tekirot[teki];
	CVector3 tekiright[teki];
	CVector3 tekifoward[teki];
	Geizi *gaizi;
	Player *Pp = nullptr;
	CVector3 ppos = CVector3::Zero;
	CVector3 teki_to_player[teki];
	float teki_to_player_vector[teki];
	CVector3 tama_to_player[teki];
	float tama_to_player_vector[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];
	float teki_siya[teki];
	prefab::CEffect* tamaEF[teki];
	CVector3 tamapos[teki];
	int tamaflag[teki];
	CVector3 tamamuki[teki];
	CVector3 teki_to_tama[teki];
	float teki_to_tama_vector[teki];
	CVector3 playerpos = CVector3::Zero;
	int time[teki];
	int damageflag[teki];
	int tekiheiflag[teki];
	float tekiHP[teki];
	int clearcount = 0;
	int soma = 0;
	CAnimation tekianimation[teki];
	CAnimationClip animclip[1];
	float Dtekiangle[teki];
	int tekianglecompF[teki];						//敵が向ききったフラグ






	//経路探査用プログラム

	
	float length(CVector3 vector);

	CVector3 EnemyPath[path];
	int path_f[teki];
	int find_f[teki];
	CVector3 teki_to_path_vector[teki][path];
	float teki_to_path[teki][path];
	int target_num[teki];
	int old_target_num[teki];
	int old_old_target_num[teki];
	int old_old_old_target_num[teki];
	int moving[teki];
	CVector3 old_pos[teki];
	int tekistop_counter[teki];
	CVector3 oldpos_to_tekipos_vector[teki];
	float oldpos_to_tekipos[teki];
	int stop_target_num[teki];
	int stop_f[teki];
	int min_f[teki];
	float minDist = FLT_MAX;
	int nearPathNo[teki];
};