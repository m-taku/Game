#include "stdafx.h"
#include "Geizi.h"
#include"tekihei.h"
#include"GameEnd.h"
Geizi::Geizi()
{
}


Geizi::~Geizi()
{
}

bool Geizi::Start()
{

	m_texture.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
	m_sprite.Init(m_texture, 400, 100);
	m_position = {-620.0,300.0,0.0};
	m_sprite.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	n_position = m_position;
	n_position += { 10.0, -10.0, 0.0};
	n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
	n_sprite.Init(n_texture, 400, 100);
	n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });

	hm_sprite.Init(m_texture, 400, 100);
	hm_position = { 250.0f,300.0f,0.0f };
	hm_sprite.Update(hm_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	hn_sprite.Init(n_texture, 400, 100);
	hn_position = hm_position;
	hn_position += { 10.0, -10.0, 0.0};
	hn_sprite.Update(hn_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,-1.0f });
	hy_texture.CreateFromDDSTextureFromFile(L"sprite/syoujun.dds");
	hy_sprite.Init(hy_texture, 110, 100);
	return true;
}
void Geizi::Update()
{
	if (HP >= 0.95) {
		HP = 0.95;
		if (HPfurag <= 0) {
			DeleteGO(haus);
			HPfurag++;
			NewGO<GameEnd>(0,"End");
		}
	}
	if (point >= 0.95) {
		point = 0.95;
		if (furag <= 0) {
			haus=NewGO<tekihei>(0, "tekihei");
			
		}
	}
	n_sprite.Update(n_position, CQuaternion::Identity, { point,0.8f,1.0f }, { 0.0f,1.0f });
	m_sprite.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	hn_sprite.Update(hn_position, CQuaternion::Identity, { 0.95f-HP,0.8f,1.0f }, { 0.0f,1.0f });
	hm_sprite.Update(hm_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	hy_sprite.Update(CVector3::Zero, CQuaternion::Identity, { 0.5f,0.5f,1.0f }, { 0.5f,0.5f });
}
void Geizi::Render(CRenderContext& rc)
{
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	n_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	hm_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	hn_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	hy_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());

}