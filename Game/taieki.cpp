#include "stdafx.h"
#include "taieki.h"
#include"math.h"
#include"camera.h"


taieki::taieki()
{
	effect = NewGO<prefab::CEffect>(0);
}
taieki::~taieki()
{
	effect->Release();
}
bool taieki::Start()
{
	for (int i = 0;i < teki;i++)
	{
		taieki_to_tekipos[i] = CVector3::Zero;
	}
	player = FindGO<Player>("Player");
	tekip = FindGO<tekihei>("tekihei");//敵兵がいたらそのインスタンスを格納する。
	/*m_taiekiModelData.Load(L"modelData/taieki.cmo");
	m_taieki.Init(m_taiekiModelData);*/
	CF = MainCamera().GetForward();
	CF.Normalize();
	tpos = player->GetPosition();//体液はプレイヤーから出されるので、体液の座標はプレイヤーと同じ座標にする。
	tpos.y += 120.0f;//体液を頭から出すために高さを調整。

	PS = player->GetMoveSpeed();//プレイヤーの移動速度を格納。

	//エフェクトの初期化。
	effect->Play(L"effect/aura1.efk");
	effect->SetPosition(tpos);
	effect->SetScale({ 10.0f,10.0f,10.0f });

	return true;
}

void taieki::ThisDelete()
{
	if (effect->IsPlay() != 1) {
		DeleteGO(this);
	}
	if (teikonFrag == true && Taim++ >= 70) {
		DeleteGO(this);
	}
}
void taieki::Update()
{
	for (int i = 0; i < teki; i++)//10回繰り返す。
	{
		if (tekip != NULL)//敵兵のインスタンスを格納していたら
		{
			tekipos2[i] = tekip->tekipos[i];                    //i番目の敵兵の座標を格納。
			tekipos2[i].y += 50.0f;                             //i番目の敵兵の座標のY座標に50.0をプラス。
			taieki_to_tekipos[i] = tekipos2[i] - tpos;          //i番目の敵兵の座標と体液の座標との差を格納。
			tekikyori[i] = sqrt(taieki_to_tekipos[i].x*taieki_to_tekipos[i].x + taieki_to_tekipos[i].y*taieki_to_tekipos[i].y + taieki_to_tekipos[i].z*taieki_to_tekipos[i].z);
			taieki_to_tekipos[i].Normalize();

			//i番目の敵兵との距離が50以下かつ、i番目の敵兵が生存していたら
			if (tekikyori[i] <= 50.0f&&tekip->tekiheiflag[i] == 1)
			{
				tekip->tekiHP[i] = 0.0f; //i番目の敵兵のHPを-1する。
				/*effect = NewGO<prefab::CEffect>(0);
				e_pos = tpos;
				effect->SetPosition(e_pos);
				effect->SetScale({ 100.0f,100.0f,100.0f });
				effect->Play(L"effect/aura.efk");*/
				DeleteGO(this);
			}

			//i番目の敵兵との距離が200以下かつ、体液のY座標が10.0以下(着弾)だったら
			if ((tekikyori[i] <= 300.0f)&&(tpos.y <= 10.0f))
			{
				tekip->tekiHP[i] -= 5.0f;//i番目の敵兵のHPを毎フレームごとに0.01ずつ減らす。
			}
		}
	}

	if (tpos.y <= 10.0f)
	{
		if (teikonFrag ==false) {
			if (Lever >= 2) {
				effect->Release();
				effect->Play(L"effect/aura3.efk");
				effect->SetScale({ 100.0f,100.0f,100.0f });
			}
			else {
				Taim = 120;
			}

			
			
			/*effect = NewGO<prefab::CEffect>(0);
			e_pos = tpos;
			effect->SetPosition(e_pos);
			effect->SetScale({100.0f,100.0f,100.0f});
			effect->Play(L"effect/aura.efk");*/

			teikonFrag = true;
		}
	}
	else {
		tpos += (CF * 2000.0f*GameTime().GetFrameDeltaTime()) + PS * GameTime().GetFrameDeltaTime();
		TS.y -= 50.0f * GameTime().GetFrameDeltaTime();
		tpos.y += TS.y;
		effect->SetPosition(tpos);
	}
	ThisDelete();//自分自身を削除するかどうかの処理をする。
	effect->SetPosition(tpos);
}
void taieki::Render(CRenderContext& rc)
{
	m_taieki.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
