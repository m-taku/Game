#include "stdafx.h"
#include "Mes.h"


Mes::Mes()
{
}


Mes::~Mes()
{
}


bool Mes::Start()
{
	m_skinModelData.Load(L"modelData/unityChan.cmo");//—«Œ^‚ğ‘‚¯
	m_skinModel.Init(m_skinModelData);
	AI::Start();

	return true;
}