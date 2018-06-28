#include "stdafx.h"
#include "Geizi.h"
#include"tekihei.h"
#include"GameEnd.h"
#include"AI.h"
Geizi::Geizi()
{
}


Geizi::~Geizi()
{
}

bool Geizi::Start()
{
	auto& human = Humans.begin();
	human++;
	for (; human < Humans.end(); human++)
	{
		AI* ka = (AI*)human[0];
		ka->GetGaizi(this);
	}

	m_texture.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
	m_sprite.Init(m_texture, 400, 100);
	m_position = {-600.0,300.0,0.0};
	m_sprite.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	n_position = m_position;
	n_position += { 10.0, -10.0, 0.0};
	n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
	n_sprite.Init(n_texture, 400, 100);
	n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });

	hm_sprite.Init(m_texture, 400, 100);
	hm_position = { 200.0f,300.0f,0.0f };
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
	if (HP_saiz > HP) {
		HP_saiz -= 0.01*kasoku;
		kasoku += 1.5;
		if (HP_saiz < HP) {
			HP_saiz = HP;
			kasoku = 0;
		}
	}
	if (HP_saiz <= 0) {
		HP_saiz = 0.0;
		if (HPfurag <= 0) {
			DeleteGO(haus);
			HPfurag++;
			NewGO<GameEnd>(0,"End");
		}
	}if (keifou_saiz < point) {
		keifou_saiz += 0.001*kasoku;
		kasoku += 0.5;
		if (keifou_saiz > point) {
			keifou_saiz = point;
			kasoku = 0.0;
		}
	}
	if (keifou_saiz >= 0.95) {
		keifou_saiz = 0.95;
		if (furag <= 0) {//1度敵兵のインスタンスが出来たらNewGOされないようにする。
			haus=NewGO<tekihei>(0, "tekihei");
			
		}
	} 


	  
	n_sprite.Update(n_position, CQuaternion::Identity, { keifou_saiz,0.8f,1.0f }, { 0.0f,1.0f });
	m_sprite.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	hn_sprite.Update(hn_position, CQuaternion::Identity, { HP_saiz,0.8f,1.0f }, { 0.0f,1.0f });
	hm_sprite.Update(hm_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });
	hy_sprite.Update(CVector3::Zero, CQuaternion::Identity, { 0.5f,0.5f,1.0f }, { 0.5f,0.5f });
}
void Geizi::PostRender(CRenderContext& rc)
{
	m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	n_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	hm_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	hn_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	hy_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}