#pragma once
#include"Geizi.h"
#include"AI_manager.h"
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
		Sneak_Many_persons,//ゾンビ化NPCの人数が多いとき(NPC総数の二分の一以上の人数)の処理(二分の一ちょうども含む)。
		Assault//アサルト(敵兵と戦う)
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
	void Play_Assault();//アサルト(敵兵と戦う)時のBGMを流しているときの処理。

private:
	AI_manager * ai_manager = nullptr;//登録されたNPCの合計人数を調べるために使用する。
	Geizi * Gauge=nullptr;//nullptrで初期化する。Geiziクラスのインスタンスが生成されない限りGaugeはnullptrのまま。
	enum BGM_Scene Scene; //switch文に使う。
	prefab::CSoundSource*m_bdm_Title = nullptr;//タイトルで流すBGM
	prefab::CSoundSource*m_bdm_Sneak1 = nullptr;//市民を強襲するときに流すBGM1
	prefab::CSoundSource*m_bdm_Sneak2 = nullptr;	 //市民を強襲するときに流すBGM2
	prefab::CSoundSource*m_bdm_Assault = nullptr;//敵兵と戦う時に流すBGM
	float ZombieNPC_Number = 0.0f;//ゾンビ化NPCの人数を格納する。
	float NPC_Goukei = 0.0f;//NPCの合計人数を記録する。
};

