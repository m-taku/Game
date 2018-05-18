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
	return true;
}
void AImove::kyorikeisan(int bangou)
{
	bekutor = game->pasu.m_pointList[bangou] - game->simin[g]->m_position;
	bekutor.y = 0.0f;
	K = game->pasu.m_pointList[bangou];
	K.y = 0.0f;
	j = bangou;
}