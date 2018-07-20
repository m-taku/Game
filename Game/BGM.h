#pragma once
#include"Geizi.h"
#include"AI_manager.h"
#include"Game.h"
class BGM : public IGameObject
{
public:
	BGM();
	~BGM();
	bool Start();
	void Update();

	enum BGM_Scene //switch文に使う。
	{
		Title,//タイトル
		Sneak_First,//スニークの最初の一回だけ動かす。
		Sneak_Fewer_people,//ゾンビ化NPCの人数が少ないとき(NPC総数の二分の一未満の人数)の処理。
		Sneak_Many_persons,//残り１分のとき。
		Game_End//ゲームが終わってフェードアウトするときの処理。
	};

	//NPCがゾンビ化した数だけカウントする。
	void SetZombie()
	{
		ZombieNPC_Number+=1.0f;
	}
	void Play_Title();//タイトルのBGMを流しているときの処理。
	void Play_Sneak_First();//スニーク時のBGMを流しているときの処理。
	void Play_Sneak_Fewer_people();
	void Play_Sneak_Many_persons();
	void Play_Game_End();

	//タイトル画面でスタートボタンが押されたことを受け取る。
	void Set_Startbutton_push();
	//タイトル画面でスタートボタンが押されたときの効果音を再生。
	void Startbutton_push_SE();

private:
	AI_manager * ai_manager = nullptr;//登録されたNPCの合計人数を調べるために使用する。
	Geizi * Gauge=nullptr;//nullptrで初期化する。Geiziクラスのインスタンスが生成されない限りGaugeはnullptrのまま。
	Game* game = nullptr;
	enum BGM_Scene Scene; //switch文に使う。
	prefab::CSoundSource*m_bdm_Title = nullptr;//タイトルで流すBGM
	prefab::CSoundSource*m_bdm_Sneak1 = nullptr;//市民を強襲するときに流すBGM1
	prefab::CSoundSource*m_bdm_Sneak2 = nullptr;	 //市民を強襲するときに流すBGM2
	prefab::CSoundSource*m_bdm_Assault = nullptr;//敵兵と戦う時に流すBGM
	float ZombieNPC_Number = 0.0f;//ゾンビ化NPCの人数を格納する。
	float NPC_Goukei = 0.0f;//NPCの合計人数を記録する。
	bool Startbutton_push_Flag = false;//タイトルでスタートボタンが押されたらtrueにする。
	float bgm_volume=1.0f;
};

