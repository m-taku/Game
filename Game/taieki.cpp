#include "stdafx.h"
#include "taieki.h"
#include"math.h"
#include"camera.h"


taieki::taieki()
{
}


taieki::~taieki()
{
}

bool taieki::Start()
{
	
	for (int i = 0;i < teki;i++)
	{
		taieki_to_tekipos[i] = CVector3::Zero;

	}
	player = FindGO<Player>("Player");
	tekip = FindGO<tekihei>("tekihei");
	m_taiekiModelData.Load(L"modelData/taieki.cmo");
	m_taieki.Init(m_taiekiModelData);
	CF = MainCamera().GetForward();
	CF.Normalize();
	tpos = player->m_position;
	tpos.y += 70.0f;
	PS = player->m_moveSpeed;
	return true;
}
void taieki::Update()
{
	
	

		tpos += (CF * 80.0f)+PS/25.0f;
	
	TS.y -= 50.0f * GameTime().GetFrameDeltaTime();
	tpos.y += TS.y;

	for (int i = 0;i < teki;i++)
	{
		if (tekip != NULL)
		{
			tekipos2[i] = tekip->tekipos[i];
			tekipos2[i].y += 50.0f;
			taieki_to_tekipos[i] = tekipos2[i] - tpos;
			tekikyori[i] = sqrt(taieki_to_tekipos[i].x*taieki_to_tekipos[i].x + taieki_to_tekipos[i].y*taieki_to_tekipos[i].y + taieki_to_tekipos[i].z*taieki_to_tekipos[i].z);
			taieki_to_tekipos[i].Normalize();
			if (tekikyori[i] <= 50.0f&&tekip->tekiheiflag[i]==1)
			{
				tekip->tekiHP[i]--;
				/*effect = NewGO<prefab::CEffect>(0);
				e_pos = tpos;
				effect->SetPosition(e_pos);
				effect->SetScale({ 100.0f,100.0f,100.0f });
				effect->Play(L"effect/aura.efk");*/
				DeleteGO(this);
			}
		}
	}

	if (tpos.y <= 0.0f)
	{
		/*effect = NewGO<prefab::CEffect>(0);
		e_pos = tpos;
		effect->SetPosition(e_pos);
		effect->SetScale({100.0f,100.0f,100.0f});
		effect->Play(L"effect/aura.efk");*/
		DeleteGO(this);
	}
	m_taieki.Update(tpos, CQuaternion::Identity, { 2.0f, 2.0f,2.0f });
}
void taieki::Render(CRenderContext& rc)
{
	m_taieki.Draw(rc, MainCamera().GetViewMatrix(), MainCamera().GetProjectionMatrix());
}
