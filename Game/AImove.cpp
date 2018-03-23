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
	Game* game = FindGO<Game>("Game");
	Size = game->m_level.m_mapChipList.size();
	iin= game->m_level.m_mapChipList[No]->m_position;//.erase(it);
	m_skinModelData.Load(L"modelData/unityChan.cmo");//ƒvƒŒƒCƒ„[‚ð‘‚¯
	m_skinModel.Init(m_skinModelData);
	m_skinModel.Update(iin, CQuaternion::Identity,{ 500.0f,500.0f,500.0f });
	No++;
	return true;
}
void AImove::Update()
{
	if (Flag == 0) {
		//int i= Level->m_mapChipList.size;
		Game* game = FindGO<Game>("Game");
		if (No <Size&&No>=0) {	
			bekutor = game->m_level.m_mapChipList[No]->m_position-iin;
			bekutor.y = 0.0f;
			K = sqrt(bekutor.x*bekutor.x + bekutor.y*bekutor.y + bekutor.z*bekutor.z);
			bekutor.Normalize();
			Fream = -1;
			No += hugo * 1;
		}
		else {
			No = 0;
			bekutor = game->m_level.m_mapChipList[No]->m_position - iin;
			bekutor.y = 0.0f;
			K = sqrt(bekutor.x*bekutor.x + bekutor.y*bekutor.y + bekutor.z*bekutor.z);
			bekutor.Normalize();
			Fream = -1;
			No += hugo * 1;
		}
		in=K / 100;
		Flag--;
	}
	else {
		iin += bekutor *in/**hugo*/;
		if (K - in*Fream <= 0)
		{
			Flag++;
		}
	}
	iin.y = 0.0f;
	Fream++;
	m_skinModel.Update(iin, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
}
void  AImove::Render(CRenderContext& rc)
{
	m_skinModel.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}