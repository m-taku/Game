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

	for (auto& human : Humans)
	{
		human->Gettekihei(NULL);
	}
	if (m_onDestroyCb != nullptr) {
		m_onDestroyCb();
	}
}

bool tekihei::Start()
{
	kikenn_texture.CreateFromDDSTextureFromFile(L"sprite/kikenn.dds");
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
	EnemyPath[45] = { -2646.0f,0.0f,2650.0f };
	EnemyPath[46] = { -2674.0f,0.0f,2650.0f };
	EnemyPath[47] = { -5329.0f,0.0f,1843.0f };
	EnemyPath[48] = { -5281.0f,0.0f,2677.0f };
	EnemyPath[49] = { -5533.0f,0.0f,4919.0f };
	EnemyPath[50] = { -4288.0f,0.0f,5380.0f };
	EnemyPath[51] = { -2680.0f,0.0f,4898.0f };
	EnemyPath[52] = { -2586.0f,0.0f,6014.0f };
	EnemyPath[53] = { -2585.0f,0.0f,7146.0f };
	EnemyPath[54] = { -4272.0f,0.0f,7144.0f };
	EnemyPath[55] = { -5467.0f,0.0f,6888.0f };
	EnemyPath[56] = { -6904.0f,0.0f,2660.0f };
	EnemyPath[57] = { -5354.0f,0.0f,940.0f };
	EnemyPath[58] = { -2618.0f,0.0f,892.0f };
	EnemyPath[59] = { -1088.0f,0.0f,2687.0f };
	EnemyPath[60] = { -1027.0f,0.0f,4814.0f };
	EnemyPath[61] = { -1076.0f,0.0f,4870.0f };
	EnemyPath[62] = { -2055.0f,0.0f,4822.0f };
	EnemyPath[63] = { -5535.0f,0.0f,6002.0f };
	EnemyPath[64] = { -5223.0f,0.0f,3950.0f };
	EnemyPath[65] = { -4423.0f,0.0f,4024.0f };
	

	for (int i = 0;i < teki;i++)//敵兵の数だけ初期化する。
	{
		kikenn_sprite[i].Init(kikenn_texture, 30, 150);
		bomEF[i] = false;
		Scale[i] = { 150.0f,150.0f,150.0f };
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
		tekistop_counter[i] = 0.0f;

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
	
//	gaizi->SatFragu();//フラグをセットして、これ以上敵兵のインスタンスが生成されないようにする。
	Pp = FindGO<Player>("Player");//プレイヤーのインスタンスを代入。
	
	for (auto& human: Humans)
	{
		human->Gettekihei(this);
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

	for (int i = 0; i < teki; i++)//敵兵の数だけ繰り返す。
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
							if (c == stop_target_num[i])
							{
								continue;
							}
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

					if (length(teki_to_path_vector[i][target_num[i]]) < 100.0f)//i番目の敵兵と一番近いパスとの距離が300未満だったら(目的地に着いたら)
					{
						old_old_old_target_num[i] = old_old_target_num[i];//二つ前のパスを三つ前のパスにする。
						old_old_target_num[i] = old_target_num[i];//一つ前のパスを二つ前のパスにする。

						old_target_num[i] = target_num[i];//目的地だったパスを一つ前のパスにする。
						stop_target_num[i] = 999;


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
						teki_to_path_vector[i][j] = EnemyPath[j] + tekiright[i] * 50.0f - tekipos[i];
						teki_to_path[i][j] = length(teki_to_path_vector[i][j]);
					}

					teki_to_path_vector[i][target_num[i]].Normalize();

					ppos = Pp->GetPosition();
					teki_to_player[i] = ppos - tekipos[i];

					teki_to_player_vector[i] = sqrt(teki_to_player[i].x*teki_to_player[i].x + teki_to_player[i].y*teki_to_player[i].y + teki_to_player[i].z*teki_to_player[i].z);

					teki_to_player[i].Normalize();//プレイヤーとi番目の敵兵との距離を正規化して向きベクトルにする。

					teki_siya[i] = acosf(tekifoward[i].Dot(teki_to_player[i]));//視野の計算

					teki_siya[i] = (180.0 / 3.14159)*teki_siya[i];
					if (teki_siya[i] <= 45.0f&&teki_to_player_vector[i] < 1500.0f)
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

				if (tekistop_counter[i] == 0.0f)
				{
					old_pos[i] = tekipos[i];
				}
				tekistop_counter[i] += 1.0f*GameTime().GetFrameDeltaTime();
				if (tekistop_counter[i] >= 5.0f)
				{
					oldpos_to_tekipos_vector[i] = old_pos[i] - tekipos[i];
					oldpos_to_tekipos[i] = length(oldpos_to_tekipos_vector[i]);
					if (oldpos_to_tekipos[i] <= 100.0f)
					{
						stop_target_num[i] = target_num[i];
						moving[i] = 0;
					}
					tekistop_counter[i] = 0.00000f;
				}

				tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
				tekiskinModel[i].Update(tekipos[i], tekirot[i], { 1.0f,1.0f,1.0f });

			}//find_fここまで

			if (gaizi->GatHPfurag() == 1)
			{
				find_f[i] = 0;
			}
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
						if (teki_to_player_vector[i] < 1000.0f&&teki_to_player_vector[i] >= 500.0f)//視認距離内かつ射程距離外だったら
						{
							tekispeed[i] = teki_to_player[i] * 300.0f;//プレイヤーへ近づく。
						}
						else {
							tekispeed[i] = CVector3::Zero;
						}

						if (teki_to_player_vector[i] < 510)//発射距離まで近づいたら

						{
							if (tamaflag[i] == 0)
							{
								tamamuki[i] = teki_to_player[i];
								tamaEF[i] = NewGO<prefab::CEffect>(0);//エフェクトの生成。
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


				tekipos[i] = m_charaCon[i].Execute(GameTime().GetFrameDeltaTime(), tekispeed[i]);
				tekiskinModel[i].Update(tekipos[i], tekirot[i], { 1.0f,1.0f,1.0f });
			}
			if (tekiHP[i] <= 0.0f)//i番目の敵兵のHPが0以下になったら
			{
				tekiheiflag[i] = 0;

			}
		}
		//i番目の敵兵のHPがまだあるときのループはここまで

		if (tekiheiflag[i] == 0)//i番目のtekiheiflagが0(i番目の敵兵のHPが0以下になった)とき
		{
			m_charaCon[i].RemoveRigidBoby();//i番目の敵兵の剛体を剛体のリストから削除する。
			clearcount++;
		}
		if (i == teki - 1)
		{
			soma = clearcount;
			clearcount = 0;
		}
		if (tekiheiflag[i] == 0)
		{
			//
			if (bom_f[i] == false)
			{
				bomEF[i] = NewGO<prefab::CEffect>(0);//エフェクトの生成。
				bomEF[i]->Play(L"effect/aura.efk");
				bomEF[i]->SetPosition({ tekipos[i].x,tekipos[i].y + 70.0f,tekipos[i].z });
				bomEF[i]->SetScale(Scale[i]);
				bom_f[i] = true;
			}
			//
			//

			if (bom_f[i] == true)
			{
				Scale[i].x -= 1.0f;
				Scale[i].y -= 1.0f;
				Scale[i].z -= 1.0f;

				bomEF[i]->SetScale(Scale[i]);
			}
			if (bom_f[i] == true && Scale[i].x <= 1.0f)
			{
				bomEF[i]->Release();
				bom_f[i] = false;
			}
			//
			if (tamaEF[i] != NULL) {//NULLじゃなかったら消す(ここでクラッシュしている。NULLが反応していない)。
				tamaEF[i]->Release();
				tamaflag[i] = 0;
				tamaEF[i] = NULL;
			}
		}

	}//敵兵の数だけ繰り返すループはここまで
	if (soma >= teki) {
		NewGO<GameEnd>(0, "End");
		DeleteGO(this);
	}
	Enemy_Discovery();
}
void tekihei::Enemy_Discovery()
{
	//float MinLength = FLT_MAX;			//距離が近いエネミー発見用
	CVector3 nearvec = CVector3::Zero;
	CVector3 Forward = CVector3::Zero;
	Forward = Pp->Getboneforward();
	//playerの右方向を求める
	CVector3 playerCross = Forward;
	for (int i = 0; i < teki; i++) {
		if (tekiheiflag[i] != 0) {
			m_enemyDiscovery[i].discovery = false;
			continue;
		}
		//敵兵のpositionを代入
		CVector4 posInScreen = tekipos[i];
		posInScreen.y += 120.0f;
		//カメラ行列を取得
		CMatrix mView = MainCamera().GetViewMatrix();
		//プロジェクション行列を取得
		CMatrix mProj = MainCamera().GetProjectionMatrix();
		//mView * mProjでカメラ空間の座標に変換
		mView.Mul(posInScreen);
		//スクリーン空間？に変換する
		mProj.Mul(posInScreen);
		//wで除算して正規化座標系（-1.0 ～1.0)にする
		posInScreen.x /= posInScreen.w;
		posInScreen.y /= posInScreen.w;
		posInScreen.z /= posInScreen.w;
		//敵兵が画面内にいるか判定
		if (posInScreen.x<1.0f && posInScreen.x>-1.0f
			&& posInScreen.y<1.0f && posInScreen.y>-1.0f
			&& posInScreen.z<1.0f && posInScreen.z>0.0f)
		{
			m_enemyDiscovery[i].discovery = false;
			m_enemyDiscovery[i].alpha = 0.0f;
			continue;
		}
		else {
			//ついでに初期化
			m_enemyDiscovery[i].discovery = false;
			m_enemyDiscovery[i].alpha = 0.0f;

			nearvec = tekipos[i] - Pp->GetPosition();
			float len = nearvec.Length();
			CVector3 axis;
			if (len <= 1000.0f)
			{
				m_enemyDiscovery[i].discovery = true;
				m_enemyDiscovery[i].alpha = 1 - (len * 0.001);
				nearvec.Normalize();
				playerCross.Cross(nearvec);
				//左手座標系なので外積をとって
				//y軸が負なら左側にいる正なら右側にいる
				if (playerCross.y < 0)
				{
					axis = CVector3::AxisZ;
				}
				else {
					axis = (CVector3::AxisZ)*-1;
				}
			}
			playerCross = Forward;
			float kakudo = acos(playerCross.Dot(nearvec));
			kakudo = CMath::RadToDeg(kakudo);
			CQuaternion Rod = CQuaternion::Identity;
			Rod.SetRotationDeg(axis, kakudo);
			kikenn_sprite[i].Update(CVector3::Zero, Rod, { 1.0f,1.0f,1.0f }, { 0.5,0.0f });
		}
	}
}
void tekihei::PostRender(CRenderContext& rc)
{
	for (int i = 0; i < teki; i++)
	{
		if (m_enemyDiscovery[i].discovery == true && m_enemyDiscovery[i].alpha>0) {
			kikenn_sprite[i].SetMulColor({ 1.0f, 1.0f, 1.0f,m_enemyDiscovery[i].alpha });
			kikenn_sprite[i].Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
		}
	}
}
void tekihei::Render(CRenderContext& rc)
{
	for (int i = 0;i < teki;i++)
	{
		if(tekiHP[i]>0.0f)
		tekiskinModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}