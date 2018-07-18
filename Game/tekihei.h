#pragma once
#include"Player.h"
#include"Geizi.h"
#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/character/tkCharacterController.h"
#define teki 51
#define path 51
class tekihei : public IGameObject
{
public:
	tekihei();
	~tekihei();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	void PostRender(CRenderContext& rc);
	void Enemy_Discovery();

	enum enemyDiscoveryIcon
	{
		null,		//見つからなかった
		left,		//プレイヤーから見て左側にいる
		right,		//プレイヤーから見て右側にいる
	};
	enemyDiscoveryIcon Icon_state = null;
	CFont m_font;



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
	CVector3 ppos = CVector3::Zero;//プレイヤーの座標。
	CVector3 teki_to_player[teki];//プレイヤーとteki番目の敵兵との距離を格納する。
	float teki_to_player_vector[teki];
	CVector3 tama_to_player[teki];
	float tama_to_player_vector[teki];
	float teki_angle[teki];
	CQuaternion trot[teki];
	float teki_siya[teki];
	prefab::CEffect* tamaEF[teki];//弾のエフェクトの配列。CEffect型
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





	//ポイント移動プログラム

	
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
	float tekistop_counter[teki];
	CVector3 oldpos_to_tekipos_vector[teki];
	float oldpos_to_tekipos[teki];
	int stop_target_num[teki];
	int stop_f[teki];
	int min_f[teki];
	//
	bool bom_f[teki];
	CVector3 Scale[teki];
	prefab::CEffect* bomEF[teki];//弾のエフェクトの配列。CEffect型。
	//
	float minDist = FLT_MAX;//一番短い距離を調べる時に使う。
	int nearPathNo[teki];//teki番目の敵兵にいちばん短い距離のパス番号を格納する。
	CVector3 teki_to_teki_vector[teki];
	float teki_to_teki_dist[teki];
	float collide_siya[teki];
	void SetOnDestoryCb(std::function<void()> cb)
	{
		m_onDestroyCb = cb;
	}
private:
	CSprite kikenn_sprite[teki];		//スプライト（中身）。


	struct enemyDiscovery
	{
		bool discovery = false;		//発見したときtrue
		float alpha = 0.0f;		//発見したときの画像の透明度
	};
	enemyDiscovery m_enemyDiscovery[teki];

	CShaderResourceView kikenn_texture;	//テクスチャ。*/
	std::function<void()> m_onDestroyCb;		//死亡したときに呼ばれるコールバック。
	bool deth_player = false;



	CVector3 pointpos[path];
	CSkinModel pointskinModel[path];					//スキンモデル。
	CSkinModelData pointskinModelData[path];
};