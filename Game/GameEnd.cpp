#include "stdafx.h"
#include "GameEnd.h"
#include"Geizi.h"
#include"Game.h"

GameEnd::GameEnd()
{
}


GameEnd::~GameEnd()
{
}
bool GameEnd::Start()
{
	Geizi* hama= FindGO<Geizi>("Geizi");
	if (hama->GatHPfurag() >= 1) {
		furgu++;
	}
	m_position = { 0.0,300.0,0.0 };
	switch (furgu)
	{
	case 0:

		you.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		break;
	case 1:
		you.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
		syuuryou.Init(you, 110, 100);
		syuuryou.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		break;
	default:
		break;
	}
	return true;
}
void GameEnd::Update()
{
	if (taim <= 300) {
		m_position.y -= 1.0;
		syuuryou.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		taim++;
	}
	else {
		DeleteGO(FindGO<Game>("Game"));
		DeleteGO(this);
	}
}

void GameEnd::Render(CRenderContext& rc)
{
	syuuryou.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
