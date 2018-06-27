#include "stdafx.h"
#include "tekihei.h"
#include"AI.h"
#include"Player.h"
#include"math.h"
#include"Geizi.h"
#include"GameEnd.h"
//#include"item.h"
tekihei::tekihei()
{
}


tekihei::~tekihei()
{
	for (int i = 0;i < teki;i++)
	{
		if (tamaEF[i] != NULL) {
			DeleteGO(tamaEF[i]);
		}
	}
	for (auto human : Humans) {
		AI* pointa = (AI*)human;
		pointa->Gettekihei(NULL);
	}
}

bool tekihei::Start()
{
	
	gaizi = FindGO<Geizi>("Geizi");
	/*animclip[0].Load(L"animData/tekiidle.tka");
	animclip[0].SetLoopFlag(true);*/


	//パスの初期化
	EnemyPath[0] = { 0.0f,0.0f,0.0f };
	EnemyPath[1] = { 0.0f,0.0f,1950.0f };
	EnemyPath[2] = { 0.0f,0.0f,4000.0f };
	EnemyPath[3] = { 0.0f,0.0f,6030.0f };
	EnemyPath[4] = { 0.0f,0.0f,8000.0f };
	EnemyPath[5] = { 0.0f,0.0f,-2010.0f };
	EnemyPath[6] = { 0.0f,0.0f,-4000.0f };
	EnemyPath[7] = { 0.0f,0.0f,-6100.0f };
	EnemyPath[8] = { 0.0f,0.0f,-8000.0f };
	EnemyPath[9] = { -8000.0f,0.0f,0.0f };
	EnemyPath[10] = { -6010.0f,0.0f,0.0f };
	EnemyPath[11] = { -4000.0f,0.0f,0.0f };
	EnemyPath[12] = { -2000.0f,0.0f,0.0f };
	EnemyPath[13] = { 2010.0f,0.0f,0.0f };
	EnemyPath[14] = { 4000.0f,0.0f,0.0f };
	EnemyPath[15] = { 6200.0f,0.0f,0.0f };
	EnemyPath[16] = { 8000.0f,0.0f,0.0f };
	EnemyPath[17] = { -8000.0f,0.0f,-8000.0f };
	EnemyPath[18] = { -8000.0f,0.0f,-6100.0f };
	EnemyPath[19] = { -8000.0f,0.0f,-4000.0f };
	EnemyPath[20] = { -8000.0f,0.0f,-2010.0f };
	EnemyPath[21] = { -8000.0f,0.0f,2050.0f };
	EnemyPath[22] = { -8000.0f,0.0f,4000.0f };
	EnemyPath[23] = { -8000.0f,0.0f,6030.0f };
	EnemyPath[24] = { -8000.0f,0.0f,8000.0f };
	EnemyPath[25] = { 8000.0f,0.0f,-8000.0f };
	EnemyPath[26] = { 8000.0f,0.0f,-6100.0f };
	EnemyPath[27] = { 8000.0f,0.0f,-4000.0f };
	EnemyPath[28] = { 8000.0f,0.0f,-2010.0f };
	EnemyPath[29] = { 8000.0f,0.0f,1950.0f };
	EnemyPath[30] = { 8000.0f,0.0f,4000.0f };
	EnemyPath[31] = { 8000.0f,0.0f,6030.0f };
	EnemyPath[32] = { 8000.0f,0.0f,8000.0f };
	EnemyPath[33] = { -6010.0f,0.0f,8000.0f };
	EnemyPath[34] = { -4000.0f,0.0f,8000.0f };
	EnemyPath[35] = { -2020.0f,0.0f,8000.0f };
	EnemyPath[36] = { 2010.0f,0.0f,8000.0f };
	EnemyPath[37] = { 4000.0f,0.0f,8000.0f };
	EnemyPath[38] = { 6200.0f,0.0f,8000.0f };
	EnemyPath[39] = { -6010.0f,0.0f,-8000.0f };
	EnemyPath[40] = { -4000.0f,0.0f,-8000.0f };
	EnemyPath[41] = { -2020.0f,0.0f,-8000.0f };
	EnemyPath[42] = { 2010.0f,0.0f,-8000.0f };
	EnemyPath[43] = { 4000.0f,0.0f,-8000.0f };
	EnemyPath[44] = { 6200.0f,0.0f,-8000.0f };

	

	for (int i = 0;i < teki;i++)//敵兵の数だけ初期化する。
	{	
		collide_siya[i] = 0.0f;
		teki_to_teki_dist[i] = 0.0f;
		teki_to_teki_vector[i] = CVector3::Zero;	                        
		nearPathNo[i] = 0;													
		tekipos[i] = EnemyPath[i];	//座標の初期化。										
		stop_target_num[i] = 999;												
		stop_f[i] = 0;														
		for (int j = 0;j < path;j++)										
		{																	
			teki_to_path[i][j]= FLT_MAX;
			teki_to_path_vector[i][j] = CVector3::Zero;
		}
		oldpos_to_tekipos_vector[i] = CVector3::Zero;
		tekistop_counter[i] = 0;

		old_old_target_num[i] = 100;
		target_num[i] = 100;
		old_target_num[i] = 100;
		old_old_old_target_num[i] = 100;
		moving[i] = 0;
		find_f[i] = 0;
		path_f[i] = 0;


		Dtekiangle[i] = 0.0f;
		tekianglecompF[i] = 0;
		tekiHP[i] = 5.0f;
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
		tekiskinModelData[i].Load(L"modelData/teki.cmo");//プレイヤーを書け
		tekiskinModel[i].Init(tekiskinModelData[i]);
		trot[i].SetRotationDeg(CVector3::AxisY, -90.0f);//回転
		tekirot[i].Multiply(trot[i]);
		tekipos[i].y += 2000.0f;            //空から降ってくるようにするため
		/*tekiskinModel[i].SetShadowCasterFlag(true);

		tekianimation[i].Init(
			tekiskinModel[i],
			animclip,
			1
		);*/
		
		/*tekipos[i].y += 1000.0f;
		tekipos[i].z += i * 150;*/
		m_charaCon[i].Init(
			40.0,			//半径。
			100.0f,			//高さ。
			tekipos[i], 	//初期位置。
			0
		);

	}//初期化ループこ↑こ↓まで
	
	gaizi->SatFragu();//フラグをセットして、これ以上敵兵のインスタンスが生成されないようにする。
	Pp = FindGO<Player>("Player");//プレイヤーのインスタンスを代入。
	auto human = Humans.begin();
	human++;
	for (; human < Humans.end(); human++) {
		AI* pointa = (AI*)human[0];
		pointa->Gettekihei(this);
	}
	return true;
}
float tekihei::length(CVector3 vector)
{
	float leng = sqrt(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
	return leng;

}
void tekihei::Update()
{
	for (int i = 0;i < teki;i++)//敵兵の数だけ繰り返す。
	{

		//tekianimation[i].Play(0);
		
		if (tekiheiflag[i] == 1)//i番目の敵兵のtekiheiflagが1(i番目の敵兵のHPがまだある)のときのループ
		{

			//敵パス
			if (find_f[i] == 0)
			{
				tekispeed[i].y -= 980.0f * GameTime().GetFrameDeltaTime();//i番目の敵兵の落下処理

				if (m_charaCon[i].IsOnGround())//i番目の敵兵が地面にいるとき
				{
					tekispeed[i].y = 0.0f;//落下を止める(地面に着地したから)


					//target_num[i] = 0;

					for (int j = 0; j < path; j++)//pathはパスの数。i番目の敵兵と全てのパスとの距離を調べる。
					{
						teki_to_path_vector[i][j] = EnemyPath[j] - tekipos[i];//j番目のパス(座標)から自分の座標を引く。
						teki_to_path[i][j] = length(teki_to_path_vector[i][j]);//自分とj番目のパスとの距離をとる。
					}
					if (moving[i] == 0)//moving[i]が0のときにいちばん短い距離のパス番号をnearPathNo[i]に保存する。
					{

						minDist = FLT_MAX;
						//nearPathNo = target_num[i];
						for (int c = 0; c < path; c++)
						{

							if (c == old_target_num[i])//ひとつ前のパスだったら
							{
								continue;
							}
							if (c == old_old_target_num[i])//ふたつ前のパスだったら
							{
								continue;
							}
							if (c == old_old_old_target_num[i]/* && c<path - 1*/)//みっつ前のパスだったら
							{
								continue;
							}
							if (minDist > teki_to_path[i][c])//一番短い距離とを比べる。
							{
								//このパスの方が近い。
								minDist = teki_to_path[i][c];
								//一番近いパスの番号を更新。
								nearPathNo[i] = c;
							}
						}
						moving[i] = 1;//
						target_num[i] = nearPathNo[i];//次に行くパスを格納する。
					}



					//for (int j = 0;j < 20;j++)
					//{
					//	for (int c = 1;c < 21;c++)
					//	{
					//		if (j == old_target_num[i] || j == old_old_target_num[i])
					//		{
					//			j++;
					//		}
					//		if (c == old_target_num[i] || c == old_old_target_num[i]||j==c)
					//		{
					//			c++;
					//		}
					//		teki_to_path_vector[i] = EnemyPath[j] - tekipos[i];
					//		teki_to_path[i][j] = length(teki_to_path_vector[i]);

					//		teki_to_path_vector[i] = EnemyPath[c] - tekipos[i];
					//		teki_to_path[i][c] = length(teki_to_path_vector[i]);

					//		if (teki_to_path[i][j] < teki_to_path[i][c])
					//		{
					//			target_num[i] = j;
					//			//if (j != old_target_num[i] && j != old_old_target_num[i])
					//			//{
					//			//	teki_to_path[i][j] = length(teki_to_path_vector[i]);//teki_to_path_vector[i].Length();
					//			//	target_num[i] = j;
					//			//}

					//		}
					//		else
					//		{
					//			target_num[i] = c;
					//		}
					//	}
					//	
					//	

					//}

					if (length(teki_to_path_vector[i][target_num[i]]) < 300.0f)//i番目の敵兵と一番近いパスとの距離が300未満だったら(目的地に着いたら)
					{
						old_old_old_target_num[i] = old_old_target_num[i];//二つ前のパスを三つ前のパスにする。
						old_old_target_num[i] = old_target_num[i];//一つ前のパスを二つ前のパスにする。

						old_target_num[i] = target_num[i];//目的地だったパスを一つ前のパスにする。



						stop_f[i] = 0;
						moving[i] = 0;//movingを0にして、i番目の敵兵にいちばん短い距離のパス番号を調べるようにする。
					}


					m_tekirot[i].MakeRotationFromQuaternion(tekirot[i]);
					tekiright[i].x = m_tekirot[i].m[0][0];
					tekiright[i].y = m_tekirot[i].m[0][1];
					tekiright[i].z = m_tekirot[i].m[0][2];
					tekiright[i].Normalize();

					tekifoward[i].x = m_tekirot[i].m[2][0];
					tekifoward[i].y = m_tekirot[i].m[2][1];
					tekifoward[i].z = m_tekirot[i].m[2][2];
					tekifoward[i].Normalize();

					for (int j = 0; j < path; j++)
					{
						teki_to_path_vector[i][j] = EnemyPath[j] + tekiright[i] * 100.0f - tekipos[i];
						teki_to_path[i][j] = length(teki_to_path_vector[i][j]);
					}

					teki_to_path_vector[i][target_num[i]].Normalize();

					ppos = Pp->GetPosition();
					teki_to_player[i] = ppos - tekipos[i];

					teki_to_player_vector[i] = sqrt(teki_to_player[i].x*teki_to_player[i].x + teki_to_player[i].y*teki_to_player[i].y + teki_to_player[i].z*teki_to_player[i].z);

					teki_to_player[i].Normalize();//プレイヤーとi番目の敵兵との距離を正規化して向きベクトルにする。

					teki_siya[i] = acosf(tekifoward[i].Dot(teki_to_player[i]));//視野の計算

					teki_siya[i] = (180.0 / 3.14159)*teki_siya[i];
					if (teki_siya[i] <= 45.0f&&teki_to_player_vector[i] < 1000.0f)
					{
						find_f[i] = 1;
						moving[i] = 0;//movingを0にして、i番目の敵兵にいちばん短い距離のパス番号を調べるようにする。
					}



					teki_angle[i] = atanf(tekiright[i].Dot(teki_to_path_vector[i][target_num[i]]));
					teki_angle[i] = (180.0 / 3.14159)*teki_angle[i];
					trot[i].SetRotationDeg(CVector3::AxisY, teki_angle[i]);//回転
					tekirot[i].Multiply(trot[i]);

					if (teki_to_path[i][target_num[i]] > 1.0f)//i番目の敵兵の次の目的地のパスとの距離が1.0f以上のとき
					{
						tekispeed[i] = teki_to_path_vector[i][target_num[i]] * 300.0f;
					}
					//衝突しないでほしいな～。
					for (int j = 0; j < teki; j++)
					{
						if (j == i)
						{
							continue;
						}
						teki_to_teki_vector[j] = tekipos[j] - tekipos[i];
						teki_to_teki_dist[j] = length(teki_to_teki_vector[j]);
						teki_to_teki_vector[j].Normalize();
						if (teki_to_teki_dist[j] < 100.0f)
						{
							collide_siya[j] = acosf(tekifoward[i].Dot(teki_to_teki_vector[j]));
							collide_siya[j] = (180.0 / 3.14159)*collide_siya[j];
							if (collide_siya[j] <= 30.0f)
							{
								tekispeed[i] += tekiright[i] * 300.0f;
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
							tamapos[i] += tamamuki[i] * 1000.0f*GameTime().GetFrameDeltaTime();
							tamaEF[i]->SetPosition(tamapos[i]);//i番目の敵兵の弾のエフェクトの座標を、同じ弾の座標と同じ座標に設定する。
						}


						if (tama_to_player_vector[i] <= 50.0f&& damageflag[i] == 0)
						{
							damageflag[i] = 1;
							gaizi->satHP(0.1);
						}
						if (damageflag[i] == 1)
						{
							tamaEF[i]->SetScale({ 100.0f,100.0f,100.0f });//i番目の敵兵の弾のエフェクトの拡大率を設定する。
							time[i]++;

							if (time[i] >= 10)
							{

								tamaEF[i]->Release();
								tamaEF[i] = NULL;
								tamaflag[i] = 0;
								time[i] = 0;
								damageflag[i] = 0;
							}
						}
						if (teki_to_tama_vector[i] >= 1000)
						{
							tamaEF[i]->Release();
							tamaEF[i] = NULL;
							tamaflag[i] = 0;
						}

					}
				}//落下しているときはこのカッコ内の処理はされない。

				tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
				tekiskinModel[i].Update(tekipos[i], tekirot[i], { 1.0f,1.0f,1.0f });

			}//find_fここまで


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////



			if (find_f[i] == 1) {
				//	tekianimation[i].Play(0);

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

				teki_to_player_vector[i] = sqrt(teki_to_player[i].x*teki_to_player[i].x + teki_to_player[i].y*teki_to_player[i].y + teki_to_player[i].z*teki_to_player[i].z);//teki_to_player??

				teki_to_player[i].Normalize();
				teki_angle[i] = atanf(tekiright[i].Dot(teki_to_player[i]));//プレイヤーに向ける計算
				teki_angle[i] = (180.0 / 3.14159)*teki_angle[i];

				teki_siya[i] = acosf(tekifoward[i].Dot(teki_to_player[i]));//視野の計算
				teki_siya[i] = (180.0 / 3.14159)*teki_siya[i];
				if (teki_siya[i] > 45.0f)
				{
					find_f[i] = 0;
				}
				if (teki_to_player_vector[i] >= 1000.0f)
				{
					find_f[i] = 0;
				}
				if (teki_siya[i] <= 45.0f&&teki_to_player_vector[i] < 1000.0f&&tekianglecompF[i] == 0)
				{
					if (Dtekiangle[i] < 1.0f)
					{
						Dtekiangle[i] += 0.01f;
					}
					if (Dtekiangle[i] >= 1.0f&&teki_siya[i] == 0.0f) {
						tekianglecompF[i] = 1;
					}
					teki_angle[i] *= Dtekiangle[i];
					trot[i].SetRotationDeg(CVector3::AxisY, teki_angle[i]);//回転

					tekirot[i].Multiply(trot[i]);
				}

				if (teki_to_tama_vector[i] >= 300.0f&&tekianglecompF[i] == 1)
				{
					Dtekiangle[i] = 0.0f;
					tekianglecompF[i] = 0;
				}
				if (teki_siya[i] <= 0.0f)
				{
					Dtekiangle[i] = 0.0f;
					tekianglecompF[i] = 0;
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
								tamapos[i].y += 85.0f;
								tamaEF[i]->Play(L"effect/aura.efk");
								tamaEF[i]->SetPosition(tamapos[i]);
								tamaEF[i]->SetScale({ 10.0f,10.0f,10.0f });
								tamaflag[i] = 1;
							}
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
						tamapos[i] += tamamuki[i] * 1000.0f*GameTime().GetFrameDeltaTime();
						tamaEF[i]->SetPosition(tamapos[i]);//i番目の敵兵の弾のエフェクトの座標を、同じ弾の座標と同じ座標に設定する。
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
							tamaEF[i] = NULL;
							tamaflag[i] = 0;
							time[i] = 0;
							damageflag[i] = 0;
						}
					}
					if (teki_to_tama_vector[i] >= 1000)
					{
						tamaEF[i]->Release();
						tamaEF[i] = NULL;
						tamaflag[i] = 0;
					}

				}

				if (tekiHP[i] <= 0.0f)//i番目の敵兵のHPが0以下になったら
				{
					tekiheiflag[i] = 0;//i番目のtekiheiflagを0にする。

				}
				tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
				tekiskinModel[i].Update(tekipos[i], tekirot[i], { 1.0f,1.0f,1.0f });
			}
		}
		//i番目の敵兵のHPがまだあるときのループはここまで

		if (tekiheiflag[i] == 0)//i番目のtekiheiflagが0(i番目の敵兵のHPが0以下になった)とき
		{
			m_charaCon[i].RemoveRigidBoby();//i番目の敵兵の剛体を剛体のリストから削除する。
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
			if (tamaEF[i] != NULL) {//NULLじゃなかったら消す(ここでクラッシュしている。NULLが反応していない)。
				//DeleteGO(tamaEF[i]);
				tamaflag[i] = 0;
			}
		}

	}//敵兵の数だけ繰り返すループはここまで
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