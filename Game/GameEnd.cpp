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
	if (hama->HPfurag >= 1) {
		furgu++;
	}
	m_position = { 0.0,300.0,0.0 };
	switch (furgu)
	{
	case 0:

		Ouba.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
		GameOuba.Init(Ouba, 110, 100);
		GameOuba.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		break;
	case 1:
		Ouba.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
		GameOuba.Init(Ouba, 110, 100);
		GameOuba.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
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
		GameOuba.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
		taim++;
	}
	else {
		DeleteGO(FindGO<Game>("Game"));
		DeleteGO(this);
	}
}

void GameEnd::Render(CRenderContext& rc)
{
	GameOuba.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
