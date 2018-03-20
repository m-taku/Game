#pragma once
#include"Human.h"
class Player;
class AI : public Human
{
public:
	AI();
	~AI();
	bool Start();
	void Update();

	void NPCNormal();
	void NPCDamage();
	void NPCZombie_Normal();
	void NPCZombie_Chase();
	void NPCZombie_Attack();

	void Render(CRenderContext& rc);
	void Turn();
	void NPCRuet(); //NPCの移動ルートを格納する。

	//メンバ変数
	enum npcpattern { //switch文に使う。
		Normal,             //市民の通常状態。
		Damage,             //ダメージを受けたとき。
		Zombie_Normal,      //ゾンビ化NPCの通常状態。
		Zombie_Chase,       //ゾンビ化NPCの追跡状態。
		Zombie_Attack       //ゾンビ化NPCの攻撃状態。
	};
	enum npcpattern pa;
	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	bool DamageFlag = false;      //ダメージを受けたかを示すフラグ。
	bool HitFlag = false;      //ダメージを与えたかを示すフラグ。
};

