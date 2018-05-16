#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include"Human.h"
#include"Game.h"
#include"Geizi.h"
#define REACH 500.0  //ゾンビの攻撃範囲。この距離まで近づいたら攻撃する。
#define PI 3.141592653589793 
class Player;
class keiroK;

class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();

	void NPCNormal();//市民の通常行動の処理。
	//void NPCEscape_NPC();//市民がゾンビNPCから逃げるときの処理。
	//void NPCEscape_Player();//市民がゾンビプレイヤーから逃げるときの処理。
	void NPCResistance_NPC();  //ゾンビに抵抗しているときの処理。
	void NPCResistance_Player();  //ゾンビに抵抗しているときの処理。
	void NPCDamage();//やられてからゾンビNPCになるまでの処理。
	void NPCFade_Out();//一般市民がステージから出ていくまでの処理。
	void NPCZombie_Normal();//ゾンビNPCの通常行動の処理。
	void NPCZombie_Chase();//ゾンビNPCが市民を追跡するときの処理。
	void NPCZombie_Attack();//特殊部隊とゾンビが戦う時の処理。
	void NPCescape();//市民がゾンビプレイヤーから逃げるときの処理。
	void NPCReturn();//戻るとき
	void NPCDeath();//死亡、消滅処理。

	void Render(CRenderContext& rc);
	void Turn();
	void DamageHantei();//ダメージ判定。
	void NPCRuet(); //NPCの移動ルートを格納する。
	float GetKyori(CVector3 a, CVector3 b);  //2つのオブジェクトの距離を計測する。
	float VectorAngleDeg(CVector3 c);  //2つのベクトルの角度を角度表記(degree)で返す。
	float Siya(CVector3 h, float g);
	float VectorAngleDeg2(CVector3 c);

protected:
	//メンバ変数
	enum npcpattern { //switch文に使う。
		Normal,             //市民の通常状態。
		Damage,             //ダメージを受けたとき。
		Resistance_NPC, //ゾンビに捕まって、抵抗しているとき。
		Resistance_Player,
		Escape,				//逃げてるとき。
		//Escape_NPC,             //市民のNPCからの逃走状態。
		//Escape_Player,       //市民のプレイヤーからの逃走状態。
		Return,				//戻るとき。
		Fade_Out,           //特殊部隊が出現して、一般市民が退場するとき。
		Zombie_Normal,      //ゾンビ化NPCの通常状態。
		Zombie_Chase,       //ゾンビ化NPCの追跡状態。
		Zombie_Attack,      //ゾンビ化NPCの攻撃状態。
		Death               //NPCの死亡。
	};


	enum npcpattern pa;
	CCharacterController m_charaCon;
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。

	CQuaternion front = CQuaternion::Identity;
	CVector3 m_forward;						//キャラの前方。
	CVector3 m_rite;						//キャラの右方向。
	CMatrix mRot;
	keiroK keiro;
	Geizi* Gaizi;
	Player* pl;
	CMatrix m_tekirot;

	CMatrix k_tekirot;
	CVector3 retu_position;
	Game* game;
	bool DamageFlag = false;      //ダメージを受けたかを示すフラグ。
	bool HitFlag = false;      //ダメージを与えたかを示すフラグ。
	bool BattleFlag = false;     //特殊部隊と戦闘をしているかを示すフラグ。
	int ForceFlag = 0;     //特殊部隊の出現を表すフラグ。
	int MyNumber = 0;               //今自分が存在しているパスの番号。
	int ZombieChaseNumber = 0;      //ゾンビが追跡を始めた時に立っていたパスの番号。
	float m_speed;
	int iNo = 0;
	int ima = 2;
	int kore = 0;
	int modori = 0;
	int da = 1;
	int muteki_count = 0;//無敵時間のカウント。
	bool muteki_Flag = false;//無敵になっているかどうかを表すフラグ。
	std::vector<int> jyunban;
	AI* Tansaku = nullptr;  //探索結果のオブジェクトを格納する。
	AI*Chase_Zombie;  //追跡してくるキャラを格納する。
};

