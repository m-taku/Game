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
	void ThisDelete();//自分自身の削除をする関数。
	void Render(CRenderContext& rc);
	CVector3 tpos = CVector3::Zero;  //体液の座標。
	CSkinModel m_taieki;             //体液のスキンモデル。
	CSkinModelData m_taiekiModelData;
	int tf = 0;
	CVector3 PS = CVector3::Zero;   //プレイヤーの移動速度(MoveSpeed)。
	CVector3 CF = CVector3::Zero;	//カメラの前方向
	CVector3 TS = CVector3::Zero;
	Player* player = nullptr;
	tekihei* tekip = nullptr;
	//CVector3 e_pos = CVector3::Zero;
	CVector3 taieki_to_tekipos[teki];//それぞれの敵兵の座標と体液の座標との差。
	CVector3 tekipos2[teki];//敵兵の、それぞれの座標を格納。
	float tekikyori[teki];//それぞれの敵兵と体液との距離。
private:
	int Lever = 2;
	int Taim = 0;
	bool teikonFrag = false;
	int counter = 0;
	prefab::CEffect* effect = nullptr;
};

