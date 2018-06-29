#pragma once
#include "tkEngine/character/tkCharacterController.h"
#include "tkEngine/graphics/animation/tkAnimation.h" //アニメーション
#include"Human.h"
#include "AI_manager.h"
#include"Geizi.h"
#include "tkEngine/culling/tkObjectFrustumCulling.h"
#include"Game.h"
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
	void GetGame(AI_manager* ka)
	{
		game = ka;
	}
	void GetGaizi(Geizi*ka)
	{
		Gaizi = ka;
	}
	void NPCNormal();							//この時はまだ知らなかった…この街にゾンビがいるなんて…（市民の通常行動の処理）
	void NPCNormal_Search();				    //おや？あれは？？？？？（市民の視野処理）
	void NPCEscape_NPC();						//に～げるんだよ～～～（市民がゾンビNPCから逃げるときの処理。）
	void NPCChase();							//やられる前に殺っちまえ～～～ーーーー（ゾンビを殴る処理）
	//void NPCEscape_Player();					//市民がゾンビプレイヤーから逃げるときの処理。
	void Gathered();							//主人様～～いまいきま～～す（ゾンビが集結する処理）
	void NPCResistance_NPC();					//俺は…こんな奴なんかに…（市民ゾンビにやられたときの処理）
	void NPCResistance_Player();				//我が人生に、一片の悔いなし！！！！（プレイヤーゾンビにやられた時の処理）
	void NPCDamage();							//俺は人間をやめるぞ～～～～～（ゾンビ化処理。）
	void NPCFade_Out();							//こんな町…もうおさらばだ（市民が町から出ていくまでの処理）
	void NPCZombie_Normal();					//ここは…どこだ（ゾンビNPCランダム徘徊の処理）
	void NPCZombie_Chase();						//お前が、死ぬまで、殴るのをやめない！！！（ゾンビNPCが市民を殴るの処理）
	void NPCZombie_Attack();					//主人様にたてつく奴は許さね～～～（特殊部隊とゾンビが戦う時の処理）//vs特殊部隊
	void NPCzombie_Return();					//殴った後帰る（いらん）
	void nearestpas();			//ド～コ行こうかな～～～（ランダム徘徊処理の初期化）
	void Retrieval_pasNo(int mokuhyou);
	void death_Animation();
	void again_move();
	void NPCGetaway();
//	void NPCzombie_Escape();					
	void NPCescape();							//こ、こんなの勝てるはずがねぇ、逃げるしかねぇ（ゾンビプレイヤーから逃げるときの処理）
	void NPCReturn();							//あそこには、何かあるはずだ！！！（指定したパスまで移行する処理）
	void FlyNPC();
	void NPCDeath();							//俺は、、こん、なところで、、、（死亡、消滅処理）
	void Zonbesiya();							//獲物はどこだ～～～（ゾンビの視野判定）
	void NPCRunangle(CVector3 kyori);
	void Render(CRenderContext& rc);
	void pasmove(int mokuhyou);		                       //パスを利用して最適なパスに移動する。
	void CharaConUpdate();
	void Chasepas(CVector3 m_position);		    //追いかける時時の基本移動処理
	void hinannpas(CVector3 m_position);		//逃げる時の基本移動処理
	void Turn();
	void NPC_Search_Zonbi();					//こ、怖くなんかねぇし(市民がゾンビを探す処理)
	void NPCRuet();							    //NPCの移動ルートを格納する。
	float GetKyori(CVector3 a, CVector3 b);     //2つのオブジェクトの距離を計測する。
	float VectorAngleDeg(CVector3 c);           //2つのベクトルの角度を角度表記(degree)で返す。
	float VectorAngleDeg(CVector3 h, CVector3 c);
	void search(CVector3 mokutekipos);								//経路探索呼び出し関数
	void Fardist_path(CVector3 m_position);
	float Siya(CVector3 h, float g);
	float takikennsau();
	void AI_Animation();
	////////////////////////////////////////////////////////////////////////
	////アニメーション関連のメンバ関数(メソッド)。                      ////
	////各サブクラスでのオーバーライドを前提とするため、中身は書かない。////
	//////////////////////////////////////////////////////////////////////////
	void Animation_Walk();					    //歩き始めと歩き続けの一連のアニメーションの処理。
	void Animation_Run();						//走り始めと走り続けの一連のアニメーションの処理。

	void Idle_Animation();
	
	void Loop_Walk_Animation();//歩き続けるときの処理。

	void Loop_Run_Animation();//走り続けるときの処理。

	void Zombie_Walk_Animation();//ゾンビ化NPCが歩き続けるときの処理。
	//void Resistance_Animation();//抵抗しているときの処理。
	void NPC_Attack_Animation();//ゾンビ化NPCが攻撃するときの処理。
	void Zombie_Ziko_Animation();
	/////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////
	CVector3 Getposition()
	{
		return m_position;
	}
	void Gettekihei(tekihei* pointa)
	{
		tekip = pointa;
	}
	CVector3 Getforward()
	{
		return m_forward;
	}
protected:
	//メンバ変数
	enum npcpattern { //switch文に使う。
		Normal,             //市民の通常状態。
		Damage,             //ダメージを受けたとき。
		Resistance_NPC, //ゾンビに捕まって、抵抗しているとき。
		Resistance_Player,
		Escape,				//逃げてるとき。
		Escape_NPC,             //市民のNPCからの逃走状態。
		Chase,
		flyNPC,
		//Escape_Player,       //市民のプレイヤーからの逃走状態。
		Return,				//戻るとき。
		Fade_Out,           //特殊部隊が出現して、一般市民が退場するとき。
		Zombie_Normal,      //ゾンビ化NPCの通常状態。
		Zonbie_Gathered,    //ゾンビの集結（プレイヤーの位置）
		Zombie_Chase,       //ゾンビ化NPCの追跡状態。
		Zombie_Attack,      //ゾンビ化NPCの攻撃状態。
		Zombie_Return,		//ゾンビ化NPCの元の位置に戻る
		Death,               //NPCの死亡。
		Getaway,
		pa_num				//paの数
	};

	enum AnimationClip {//各アニメーションのクリップ。
		Idle,              //立ち状態
		Loop_Walk,         //歩き続け
		Loop_Run,          //走り続け
		Zombie_Walk,       //ゾンビ化NPCの歩き           
		//Resistance,        //抵抗
		//NPC_Attack      //ゾンビ化NPCの攻撃
		Animnum           //AnimationClipの総数
	};
	enum animation {
		shiminidle,
		shiminwalk,
		shiminrun,
		shiminattack,
		Zonbiwalk,
		Zonbiattack,
		Zonbi_zico,
		animnum
	};
	CAnimation ai_NPCAnimation;				//アニメーション。
	CAnimationClip ai_NPCAnimationClips[animnum];	//アニメーションクリップ。
	CShaderResourceView zondi;

	enum npcpattern pa;
	int satForceFlag()
	{
		 ForceFlag = true;     //特殊部隊の出現を表すフラグ。
	}

	CSkinModel m_skinModel;					//スキンモデル。
	CSkinModelData m_skinModelData;			//スキンモデルデータ。
	AI_manager* game;
	float m_speed;
	bool ziko_frag = false;
	car* Car;
	Geizi* Gaizi;
	Player* pl;
	CVector3 previous_position=CVector3::Zero;
	int taime = 0;
	bool HitFlag = false;      //ダメージを与えたかを示すフラグ。
private:
	bool muteki_Flag = false;//無敵になっているかどうかを表すフラグ。
	bool DamageFlag = false;      //ダメージを受けたかを示すフラグ。
	bool BattleFlag = false;     //特殊部隊と戦闘をしているかを示すフラグ。
	bool Raifu_f = false;
	int MyNumber = 0;               //今自分が存在しているパスの番号。
	int ZombieChaseNumber = 0;      //ゾンビが追跡を始めた時に立っていたパスの番号。
	float NPCHP=100.0f;
	float NPCMAXHP = 100.0f;
	int iNo = 0;
	int ima = 0;
	int kore = 0;
	int modori = 0;
	int da = 0;
	int mikata = 0;
	int muteki_count = 0;//無敵時間のカウント。
	int Chasefrag = 0;
	bool ForceFlag = false;     //特殊部隊の出現を表すフラグ。
	std::vector<int>::iterator pasu;
	int stoptaim = 0;
	//CVector3 m_movespeed=CVector3::Zero;
	float gravity = -3*(980.0f * GameTime().GetFrameDeltaTime());
	int No = 0;
	int no = 0;
	float sinsoku = 0.0f;
	AI* Tansaku = nullptr;  //探索結果のオブジェクトを格納する。o
	AI* lam;
	CVector3 m_movespeed = CVector3::Zero;		//移動速度。
	AImove* work;
	CVector3 m_position = CVector3::Zero;
	float atekfrag = 0;
	float escapecaku = 30.0f;
	int radam = 0;
	int mokuhyouNo = 0;			//目的地のパス番号の入っている＜配列番号＞
	tekihei* tekip;
	int mokuhyou=1;					//目的地のパス番号
	std::vector<AI*> mikatalest;
	bool keikai_f = false;
	CVector3 retu_position = CVector3::Zero;
	int mobe = 500;
	std::vector<Human*>::iterator AIrest;

	float atakkukyori = 200.0f;
	int furag = 0;
	bool kannkaku = false;
	int Leftfrag = 0;
	int destination_Leftfrag = 0;
	bool kaiten = false;
	CObjectFrustumCulling m_objectFrustumCulling;
	float angle = 0.0f;
	CVector3 Pboneforward = CVector3::Zero;
	CQuaternion Crot = CQuaternion::Identity;
	CCharacterController A_charaCon;
	CQuaternion m_rotation = CQuaternion::Identity;	//回転。
	CQuaternion front = CQuaternion::Identity;
	CVector3 m_forward;						//キャラの前方。
	CVector3 m_rite;						//キャラの右方向。
	CMatrix mRot;
	CMatrix m_tekirot;
	CMatrix k_tekirot;
	car* ziko_car;
	CVector3 before_m_position = CVector3::Zero;		//一つ前の座標。
	std::vector<int> jyunban;
	int counta = 0;
	CVector3 flydist=CVector3::Zero;
	AI* Chawse_Zombie;  //追跡してくるキャラを格納する。
};

