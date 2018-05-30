#include "stdafx.h"
#include "tekihei.h"
#include"Player.h"
#include"math.h"
#include"Geizi.h"
#include"GameEnd.h"
#include"item.h"
tekihei::tekihei()
{
}


tekihei::~tekihei()
{
	for (int i = 0;i < teki;i++)
	{
		if (tamaEF[i] != NULL) {
			tamaEF[i]->Release();
		}
	}
}

bool tekihei::Start()
{
	
	gaizi = FindGO<Geizi>("Geizi");
	//animclip[0].Load(L"animData/tekiidle.tka");
	//animclip[1].Load(L"animData/run.tka");
	//animclip[0].SetLoopFlag(true);
	//animclip[1].SetLoopFlag(true);

	NewGO<item>(0, "item");
	for (int i = 0;i < teki;i++)
	{
		
		tekiHP[i] = 5;
		tekiheiflag[i] = 1;
		damageflag[i] = 0;
		time[i] = 0;
		tama_to_player[i] = CVector3::Zero;
		tama_to_player_vector[i] = 0.0f;
		teki_to_tama_vector[i] = 0.0f;
		teki_to_tama[i] = CVector3::Zero;
		tamamuki[i] = CVector3::Zero;
		tamaEF[i] = nullptr;
		tamaflag[i] = 0;
		tamapos[i] = CVector3::Zero;
		tekispeed[i] = CVector3::Zero;
		teki_angle[i] = 0.0f;
		trot[i] = CQuaternion::Identity;
		tekirot[i] = CQuaternion::Identity;
		tekipos[i] = CVector3::Zero;
		tekipos[i].x = 3600.0f;
		tekipos[i].z = 0.0f;
		tekiskinModelData[i].Load(L"modelData/teki.cmo");//プレイヤーを書け
		tekiskinModel[i].Init(tekiskinModelData[i]);
		trot[i].SetRotationDeg(CVector3::AxisY, -90.0f);//回転
		tekirot[i].Multiply(trot[i]);
		tekiskinModel[i].SetShadowCasterFlag(true);

		/*tekianimation[i].Init(
			tekiskinModel[i],
			animclip,
			1
		);*/
		
		tekipos[i].y += 1000.0f;
		tekipos[i].z += i * 150;
		m_charaCon[i].Init(
			50.0,			//半径。
			100.0f,			//高さ。
			tekipos[i], 	//初期位置。
			0
		);
	}
	gaizi->SatFragu();
	Pp = FindGO<Player>("Player");
	return true;
}

void tekihei::Update()
{
	for (int i = 0;i < teki;i++)
	{
		//tekianimation[i].Play(0);
		
		if (tekiheiflag[i] == 1)
		{
			m_tekirot[i].MakeRotationFromQuaternion(tekirot[i]);
			tekiright[i].x = m_tekirot[i].m[0][0];
			tekiright[i].y = m_tekirot[i].m[0][1];
			tekiright[i].z = m_tekirot[i].m[0][2];
			tekiright[i].Normalize();

			tekifoward[i].x = m_tekirot[i].m[2][0];
			tekifoward[i].y = m_tekirot[i].m[2][1];
			tekifoward[i].z = m_tekirot[i].m[2][2];
			tekifoward[i].Normalize();

			ppos = Pp->GetPosition();
			teki_to_player[i] = ppos - tekipos[i];

			teki_to_player_vector[i] = sqrt(teki_to_player[i].x*teki_to_player[i].x + teki_to_player[i].y*teki_to_player[i].y + teki_to_player[i].z*teki_to_player[i].z);

			teki_to_player[i].Normalize();
			teki_angle[i] = atanf(tekiright[i].Dot(teki_to_player[i]));//プレイヤーに向ける計算
			teki_angle[i] = (180.0 / 3.14159)*teki_angle[i];

			teki_siya[i] = acosf(tekifoward[i].Dot(teki_to_player[i]));//視野の計算
			teki_siya[i] = (180.0 / 3.14159)*teki_siya[i];
			if (teki_siya[i] <= 45.0f&&teki_to_player_vector[i]<1000.0f)
			{
				trot[i].SetRotationDeg(CVector3::AxisY, teki_angle[i]);//回転
				tekirot[i].Multiply(trot[i]);
			}


			tekispeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();
			if (m_charaCon[i].IsOnGround()) {
				//地面についた。
				tekispeed[i].y = 0.0f;
				if (teki_siya[i] <= 45.0f)
				{
					if (teki_to_player_vector[i] < 1000.0f&&teki_to_player_vector[i] >= 500.0f)
					{
						tekispeed[i] = teki_to_player[i] * 300.0f;
					}
					else {
						tekispeed[i] = CVector3::Zero;
					}
					if (teki_to_player_vector[i] < 510)
					{
						if (tamaflag[i] == 0)
						{
							tamamuki[i] = teki_to_player[i];
							tamaEF[i] = NewGO<prefab::CEffect>(0);
							tamapos[i] = tekipos[i];
							tamapos[i].y += 70.0f;
							tamaEF[i]->Play(L"effect/aura.efk");
							tamaEF[i]->SetPosition(tamapos[i]);
							tamaEF[i]->SetScale({ 10.0f,10.0f,10.0f });
							tamaflag[i] = 1;
						}
					}

				}
				if (tamaflag[i] == 1)
				{
					playerpos = Pp->GetPosition();
					playerpos.y += 50.0f;
					tama_to_player[i] = playerpos - tamapos[i];
					tama_to_player_vector[i] = sqrt(tama_to_player[i].x*tama_to_player[i].x + tama_to_player[i].y*tama_to_player[i].y + tama_to_player[i].z*tama_to_player[i].z);

					teki_to_tama[i] = tamapos[i] - tekipos[i];
					teki_to_tama_vector[i] = sqrt(teki_to_tama[i].x*teki_to_tama[i].x + teki_to_tama[i].y*teki_to_tama[i].y + teki_to_tama[i].z*teki_to_tama[i].z);
					if (tama_to_player_vector[i] > 50.0f && damageflag[i] == 0)
					{
						tamapos[i] += tamamuki[i] * 30.0f;
						tamaEF[i]->SetPosition(tamapos[i]);
					}


					if (tama_to_player_vector[i] <= 50.0f&& damageflag[i] == 0)
					{
						damageflag[i] = 1;
						gaizi->satHP(0.1);
					}
					if (damageflag[i] == 1)
					{
						tamaEF[i]->SetScale({ 100.0f,100.0f,100.0f });
						time[i]++;

						if (time[i] >= 10)
						{
							tamaEF[i]->Release();
							tamaflag[i] = 0;
							time[i] = 0;
							damageflag[i] = 0;
						}
					}
					if (teki_to_tama_vector[i] >= 1000)
					{
						tamaEF[i]->Release();
						tamaflag[i] = 0;
					}

				}
			}
			if (tekiHP[i] == 0)
			{
				tekiheiflag[i] = 0;

			}
			tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
			tekiskinModel[i].Update(tekipos[i], tekirot[i], {2.0f,2.0f,2.0f});
		}
		if (tekiheiflag[i] == 0)
		{
			m_charaCon[i].RemoveRigidBoby();
			clearcount++;
		}
		if (clearcount >= teki)
		{
			soma = clearcount;
		}
		if (i == teki - 1)
		{
			clearcount = 0;
		}
		if (tekiheiflag[i]==0)
		{
			if(tamaEF[i]!=NULL)
			tamaEF[i]->Release();
			tamaflag[i] = 0;
		}
	}
	if (soma >= teki) {
		NewGO<GameEnd>(0, "End");
		DeleteGO(this);
	}
}

void tekihei::Render(CRenderContext& rc)
{
	for (int i = 0;i < teki;i++)
	{
		if(tekiheiflag[i]==1)
		tekiskinModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}