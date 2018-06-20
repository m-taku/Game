#include "stdafx.h"
#include "AI_manager.h"
#include"AI.h"
#include"Osu.h"
#include"Mes.h"
#include"Dog.h"
AI_manager* AI_ado;
AI_manager::AI_manager()
{
	AI_ado = this;
	wchar_t moveFilePath[256];
	swprintf_s(moveFilePath, L"lever/levalAI%d%d.tks", 0, 2);
	pasu[0].Load(moveFilePath, No);
	No = 1;
	swprintf_s(moveFilePath, L"lever/levalAI%d%d.tks", 2, 2);
	pasu[1].Load(moveFilePath, No);
	No = 0;
	da.push_back(AIR1);
	da.push_back(AIR2);
	da.push_back(AIR3);
	da.push_back(AIR4);
	da.push_back(AIR5);
	da.push_back(AIR6);
	da.push_back(AIR7);
	da.push_back(AIR8);
	da.push_back(AIR9);
	da.push_back(AIR10);
	da.push_back(AIR11);
	da.push_back(AIR12);
	da.push_back(AIR13);
	da.push_back(AIR14);
	da.push_back(AIR15);
	da.push_back(AIR16);
	da.push_back(AIR17);
	da.push_back(AIR18);
	da.push_back(AIR19);
	da.push_back(AIR20);
	da.push_back(AIR21);
	da.push_back(AIR22);
	da.push_back(AIR23);
	da.push_back(AIR24);
	da.push_back(AIR25);
	da.push_back(AIR26);
	for (int k = 0; k < da.size(); k++) {
		AI* AIR = NewGO<AI>(0, "AI");
		AIR->GetGame(this);
		Rsimin.push_back(AIR);
		RAIseizon.push_back(1);
	}
	No = 0;
	Leftfrag = 1;
	da2.push_back(AIL1);
	da2.push_back(AIL2);
	da2.push_back(AIL3);
	da2.push_back(AIL4);
	da2.push_back(AIL5);
	da2.push_back(AIL6);
	da2.push_back(AIL7);
	da2.push_back(AIL8);
	da2.push_back(AIL9);
	da2.push_back(AIL10);
	da2.push_back(AIL11);
	da2.push_back(AIL12);
	da2.push_back(AIL13);
	da2.push_back(AIL14);
	da2.push_back(AIL15);
	da2.push_back(AIL16);
	da2.push_back(AIL17);
	da2.push_back(AIL18);
	da2.push_back(AIL19);
	da2.push_back(AIL20);
	da2.push_back(AIL21);
	da2.push_back(AIL22);
	da2.push_back(AIL23);
	da2.push_back(AIL24);
	da2.push_back(AIL25);
	for (int k = 0; k < da2.size(); k++) {
		AI* AIL = NewGO<AI>(0, "Osu");
		AIL->GetGame(this);
		Lsimin.push_back(AIL);
		LAIseizon.push_back(1);
	}
	No = 0;
}


AI_manager::~AI_manager()
{
	for (int k = 0; k < Rsimin.size(); k++) {
		if (RAIseizon[k] >= 1) {
			DeleteGO(Rsimin[k]);
		}
	}
	for (int k = 0; k < Lsimin.size(); k++) {

		if (LAIseizon[k] >= 1) {
			DeleteGO(Lsimin[k]);
		}
	}

}
bool AI_manager::Start()
{
	return true;
}