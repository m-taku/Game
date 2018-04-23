#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include"Human.h"
#include"Game.h"
class Player;
class keiroK;

class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();
	void NPCNormal();
	void NPCDamage();
	void NPCescape();
	void NPCReturn();
	void NPCZombie_Normal();
	void NPCZombie_Chase();
	void NPCZombie_Attack();
	void Render(CRenderContext& rc);
	void Turn();
	void NPCRuet(); //NPCの移動ルートを格納する。
	float GetKyori(CVector3 a, CVector3 b);  //2つのオブジェクトの距離を計測する。
	float VectorAngleDeg(CVector3 c);  //2つのベクトルの角度を角度表記(degree)で返す。

	//メンバ変数
	enum npcpattern { //switch文に使う。
		Normal,             //市民の通常状態。
		Damage,             //ダメージを受けたとき。
		Escape,				//逃げてるとき。
		Return,				//戻るとき。
		Zombie_Normal,      //ゾンビ化NPCの通常状態。
		Zombie_Chase,       //ゾンビ化NPCの追跡状態。
		Zombie_Attack       //ゾンビ化NPCの攻撃状態。
	};
	enum npcpattern pa;
	CCharacterController m_charaCon;
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	CVector3 m_forward;						//キャラの前方。
	CVector3 m_rite;						//キャラの右方向。
	CMatrix mRot;
	keiroK* keiro;
	Player* pl;
	CVector3 retu_position;
	Game* game;
	bool DamageFlag = false;      //ダメージを受けたかを示すフラグ。
	bool HitFlag = false;      //ダメージを与えたかを示すフラグ。
	bool BattleFlag = false;     //特殊部隊と戦闘をしているかを示すフラグ。
	bool ForceFlag = false;     //特殊部隊の出現を表すフラグ。
	int MyNumber = 0;               //今自分が存在しているパスの番号。
	int ZombieChaseNumber = 0;      //ゾンビが追跡を始めた時に立っていたパスの番号。
	float m_speed;
	int iNo = 0;
	int ima = 2;
	int kore = 0;
	int modori = 0;
	int da = 1;
};

