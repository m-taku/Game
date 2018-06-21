#pragma once
#include"Geizi.h"
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
		Sneak,//スニーク
		Assault//アサルト(敵兵と戦う)
	};

	void Play_Title();//タイトルのBGMを流しているときの処理。
	void Play_Sneak();//スニーク時のBGMを流しているときの処理。
	void Play_Assault();//アサルト(敵兵と戦う)時のBGMを流しているときの処理。

private:
	Geizi * Gauge=nullptr;//nullptrで初期化する。Geiziクラスのインスタンスが生成されない限りGaugeはnullptrのまま。
	enum BGM_Scene Scene; //switch文に使う。
	prefab::CSoundSource*m_bdm_Title = nullptr;//タイトルで流すBGM
	prefab::CSoundSource*m_bdm_Sneak = nullptr;//市民を強襲するときに流すBGM
	prefab::CSoundSource*m_bdm_Assault = nullptr;//敵兵と戦う時に流すBGM
};

