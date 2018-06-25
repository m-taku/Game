#pragma once
#include"Player.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 45
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
	CQuaternion tekirot[teki];//敵の回転
	CMatrix m_tekirot[teki];
	CVector3 tekiright[teki];//敵兵の右方向。
	CVector3 tekifoward[teki];//敵兵の前方方向。
	Geizi *gaizi;//ゲージのインスタンスを入れるポインタ。
	Player *Pp;//プレイヤーのインスタンスを入れるポインタ。
	CVector3 ppos = CVector3::Zero;
	CVector3 teki_to_player[teki];
	float teki_to_player_vector[teki];
	CVector3 tama_to_player[teki];
	float tama_to_player_vector[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];
	float teki_siya[teki];
	prefab::CEffect* tamaEF[teki];//弾のエフェクトの配列。CEffect型。
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
	int tekianglecompF[teki];





	//経路探査用プログラム

	
	float length(CVector3 vector);

	CVector3 EnemyPath[path];//それぞれの敵兵の初期位置を格納する。
	int path_f[teki];
	int find_f[teki];
	CVector3 teki_to_path_vector[teki][path];
	float teki_to_path[teki][path];//teki番目の敵兵とpath番目のパスとの距離を格納する。
	int target_num[teki];//teki番目の敵兵の次の目的地のパスを格納する。
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
	float minDist = FLT_MAX;//一番短い距離を調べる時に使う。
	int nearPathNo[teki];//teki番目の敵兵にいちばん短い距離のパス番号を格納する。
	CVector3 teki_to_teki_vector[teki];
	float teki_to_teki_dist[teki];
	float collide_siya[teki];
};