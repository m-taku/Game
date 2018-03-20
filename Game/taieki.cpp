#include "stdafx.h"
#include "taieki.h"

#include"camera.h"


taieki::taieki()
{
}


taieki::~taieki()
{
}

bool taieki::Start()
{
	player = FindGO<Player>("Player");
	m_taiekiModelData.Load(L"modelData/taieki.cmo");
	m_taieki.Init(m_taiekiModelData);
	CF = MainCamera().GetForward();
	CF.Normalize();
	tpos = player->m_position;
	tpos.y += 80.0f;
	
	return true;
}
void taieki::Update()
{
	tpos += CF * 60.0f;
	
	TS.y -= 50.0f * GameTime().GetFrameDeltaTime();
	tpos.y += TS.y;
	if (tpos.y <= 0.0f)
	{
		DeleteGO(this);
	}
	m_taieki.Update(tpos, CQuaternion::Identity, { 2.0f, 2.0f,2.0f });
}
void taieki::Render(CRenderContext& rc)
{
	m_taieki.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
