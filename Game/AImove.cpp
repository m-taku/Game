#include "stdafx.h"
#include "AImove.h"
#include"Level.h"
#include"math.h"
#include"Game.h"
#include"Pasu.h"
#include"keiroK.h"
#include"AI.h"
AImove::AImove()
{
}


AImove::~AImove()
{
}


bool AImove::Start()
{
	game = FindGO<Game>("Game");
	g = game->No;
	//for (int i = 0; i <10; i++) {
	//	if (game->pasu[i].m_pointList.size() == NULL) {
	//		break;
	////	}
	//	for (int ko=0; ko< game->keiro->jyunban.size(); ko++) {
	//		No[ko]] = game->keiro->jyunban[ko];

	//	}
	Size = 4;//game->pasu.m_pointList.size();
	for (int i = 0; i < 4; i++) {
		No[i] = game->da[g][i];
	}
	//.erase(it);
//	m_skinModelData.Load(L"modelData/unityChan.cmo");//ÉvÉåÉCÉÑÅ[ÇèëÇØ
	//m_skinModel[i].Init(m_skinModelData[i]);
//	m_skinModel[i].Update(iin[i], CQuaternion::Identity, { 500.0f,500.0f,500.0f });
	//j++;
	in = 500.0f;
	Fream = 0;
	Flag = 0;
	iin.y = 0.0f;
	return true;
}
void AImove::Update()
{
	//if (Flag == 0) {
	//	if (ima < Size && ima >= 0) {
	//		kyorikeisan(No[ima]);
	//	}
	//	else {/*
	//		hugo = hugo * -1;*/
	//		ima = 0;//+= hugo;
	//		kyorikeisan(No[ima]);
	//	}
	//	Flag--;
	//}
	//else {
	//	iin += bekutor * in/**hugo*/;
	//	game->simin[g]->m_position = iin;
	//	if (K - in * Fream <= 10 && K - in * Fream >= -10)
	//	{
	//		Flag++;
	//	}
	//	Fream++;
	//	iin.y = 0.0f;
	//}
}
void  AImove::Render(CRenderContext& rc)
{
	//for (int i = 0; i < j; i++) {
	//	m_skinModel[i].Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
	//}
}
void AImove::kyorikeisan(int bangou)
{
	bekutor = game->pasu.m_pointList[bangou] - game->simin[g]->m_position;
	bekutor.y = 0.0f;
	K = game->pasu.m_pointList[bangou];
	K.y = 0.0f;
	bekutor.Normalize();
	Fream = 0;
}