#include "stdafx.h"
#include "AImove.h"
#include"Level.h"
#include"math.h"
#include"Game.h"
#include"Pasu.h"
#include"keiroK.h"
AImove::AImove()
{
}


AImove::~AImove()
{
}


bool AImove::Start()
{
	game = FindGO<Game>("Game");/*
	int x = game->pasu[0].GetNumPoint();*/
	for (int i = 0; i <10; i++) {
		if (game->pasu[i].m_pointList.size() == NULL) {
			break;
		}
		for (; kosuu[i] < game->keiro.jyunban.size(); kosuu[i]++) {
			No[kosuu[i]] = game->keiro.jyunban[kosuu[i]];

		}
		//Size[i] = game->pasu[i].GetNumPoint();
		iin[i] = game->pasu[i].m_pointList[No[0]];//.erase(it);
		m_skinModelData[i].Load(L"modelData/unityChan.cmo");//ÉvÉåÉCÉÑÅ[ÇèëÇØ
		m_skinModel[i].Init(m_skinModelData[i]);
		m_skinModel[i].Update(iin[i], CQuaternion::Identity, { 500.0f,500.0f,500.0f });
		j++;
		K[i] = 0.0f;
		in[i] = 0.0f;
		Fream[i] = 0;
		Flag[i] = 0;
	
	}
	return true;
}
void AImove::Update()
{
	for (int i = 0; i < j; i++) {
		if (Flag[i] == 0) {
			if (ima < kosuu[i] && ima >=0) {
				kyorikeisan(i);
			}
			else {
				hugo = hugo * -1;
				ima += hugo;
				kyorikeisan(i);
			}
			in[i] = K[i] / 100;
			Flag[i]--;
		}
		else {
			iin[i] += bekutor[i] * in[i]/**hugo*/;
			if (K[i] - in[i] * Fream[i] <= 0)
			{
				Flag[i]++;
			}
			Fream[i]++;
			iin[i].y = 0.0f;
		}

		m_skinModel[i].Update(iin[i], CQuaternion::Identity, { 1.0f,1.0f,1.0f });
	}
}
void  AImove::Render(CRenderContext& rc)
{
	for (int i = 0; i < j; i++) {
		m_skinModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	}
}
void AImove::kyorikeisan(int bangou)
{
	bekutor[bangou] = game->pasu[bangou].m_pointList[No[ima]-1] - iin[bangou];
	bekutor[bangou].y = 0.0f;
	K[bangou] = sqrt(bekutor[bangou].x*bekutor[bangou].x + bekutor[bangou].y*bekutor[bangou].y + bekutor[bangou].z*bekutor[bangou].z);
	bekutor[bangou].Normalize();
	Fream[bangou] = 0;
	ima += hugo;
}