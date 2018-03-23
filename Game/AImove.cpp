#include "stdafx.h"
#include "AImove.h"
#include"Level.h"
#include"math.h"
#include"Game.h"
AImove::AImove()
{
}


AImove::~AImove()
{
}

bool AImove::Start()
{
	game = FindGO<Game>("Game");
	for (int i = 0; i < 10; i++) {
		if (game->m_level[i].m_mapChipList.size() == NULL) {
			break;
		}
		No[i] = 0;
		Size[i] = game->m_level[i].m_mapChipList.size();
		iin[i] = game->m_level[i].m_mapChipList[No[i]]->m_position;//.erase(it);
		m_skinModelData[i].Load(L"modelData/unityChan.cmo");//ÉvÉåÉCÉÑÅ[ÇèëÇØ
		m_skinModel[i].Init(m_skinModelData[i]);
		m_skinModel[i].Update(iin[i], CQuaternion::Identity, { 500.0f,500.0f,500.0f });
		j++;
		K[i] = 0.0f;
		in[i] = 0.0f;
		Fream[i] = 0;
		Flag[i] = 0;
		No[i] = 1;
	}
	return true;
}
void AImove::Update()
{
	for (int i = 0; i < j; i++) {
		if (Flag[i] == 0) {
			if (No[i] < Size[i] && No[i] >= 0) {
				bekutor[i] = game->m_level[i].m_mapChipList[No[i]]->m_position - iin[i];
				bekutor[i].y = 0.0f;
				K[i] = sqrt(bekutor[i].x*bekutor[i].x + bekutor[i].y*bekutor[i].y + bekutor[i].z*bekutor[i].z);
				bekutor[i].Normalize();
				Fream[i] = 0;
				No[i] += hugo * 1;
			}
			else {
				No[i] = 0;
				bekutor[i] = game->m_level[i].m_mapChipList[No[i]]->m_position - iin[i];
				bekutor[i].y = 0.0f;
				K[i] = sqrt(bekutor[i].x*bekutor[i].x + bekutor[i].y*bekutor[i].y + bekutor[i].z*bekutor[i].z);
				bekutor[i].Normalize();
				Fream[i] = 0;
				No[i] += hugo * 1;
			}
			in[i] = K[i] / 500;
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