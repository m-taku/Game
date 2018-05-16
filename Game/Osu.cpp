#include "stdafx.h"
#include "Osu.h"


Osu::Osu()
{
}


Osu::~Osu()
{
}

bool Osu::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//男性型を書け
	m_skinModel.Init(m_skinModelData);
	AI::Start();

	return true;
}

//NPCゾンビに抵抗しているときの処理。AIクラスの同じメソッド(メンバ関数)をオーバーライドする。
void Osu::NPCResistance_NPC() 
{
	pa = Damage;
}

//プレイヤーゾンビに抵抗しているときの処理。AIクラスの同じメソッド(メンバ関数)をオーバーライドする。
void Osu::NPCResistance_Player()
{
	static int count = 30;//初期値。
	static int i = 0;//毎フレームカウントする。

	i++;//毎フレーム実行。
	
		
		if (i > 7) {//8フレーム以上で作動する。
			count++;
			i = 0;
		}

		if (Pad(0).IsTrigger(enButtonB)) { //Bボタンが押されたら
			count--;
		}

		if (count <= 0) {//countが0以下になったら
			count = 30;//値を初期化。
			i = 0;//フレームカウントの値を初期化。
			pa = Damage;//パターンをダメージに変える。
		}

		if (count >= 60) {//countが60以上になったら
			count = 30;//値を初期化。
			i = 0;//フレームカウントの値を初期化。
			muteki_Flag = true;//無敵フラグをあげて、無敵化する。
			pa = Return;//パターンをリターンに変える。
		}
	
}