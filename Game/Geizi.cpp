#include "stdafx.h"
#include "Geizi.h"
#include"tekihei.h"
#include"GameEnd.h"
#include"AI.h"
#include"Player.h"
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
		AI* ka = (AI*)*human;
		ka->GetGaizi(this);
	}
	player = FindGO<Player>("Player");
	//m_texture.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
	//m_sprite.Init(m_texture, 400, 100);
	//m_position = {-600.0,300.0,0.0};
	//m_sprite.Update(m_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });

	//n_position = m_position;
	//n_position += { 10.0, -10.0, 0.0};
	//n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
	//n_sprite.Init(n_texture, 400, 100);
	//n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.0f,1.0f });

	HP_texture.CreateFromDDSTextureFromFile(L"sprite/damage.dds");
	hm_sprite.Init(HP_texture, 1280,720);
	hm_sprite.Update(CVector3::Zero, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	hy_texture.CreateFromDDSTextureFromFile(L"sprite/syoujun.dds");
	hy_sprite.Init(hy_texture, 110, 100);
	Dame = idor;
	return true;
}
void Geizi::Update()
{	
	if (HPfurag >= 1)
	{
		HP_saiz += 0.1*GameTime().GetFrameDeltaTime();
		if (HP_saiz >= 1.0f)
		{
			HP_saiz = 1.0f;
			player->Playoki();
			if (player->anine_Playing())
			{
				HP = 1.0f;
				HPfurag = 0;
				player->trueGame();
			}
		}
	}
	if (HP <= 0) {
		HP = 0.0;
		if (HPfurag <= 0) {
			HPfurag++; 
			player->falseGame();
			player->Playkoke();
			//NewGO<GameEnd>(0, "End");
		}
	}
	
	switch (Dame)
	{
	case UP:
		if (HP_saiz >= HP)
		{
			HP_saiz -=0.2*GameTime().GetFrameDeltaTime();
			if (HP_saiz <= HP)
			{
				HP_saiz = HP;
				Dame = Down;
			}
		}
		break;
	case Down:
		if (HP_saiz <=HP+0.2)
		{
			HP_saiz += 0.2*GameTime().GetFrameDeltaTime();
			if (HP_saiz >= HP + 0.2)
			{
				HP_saiz = HP+0.2;
				Dame = UP;
			}
		}
		break;
	case idor:
		break;
	default:
		break;
	}
	//}if (keifou_saiz < point) {
	//	keifou_saiz += 0.001*kasoku;
	//	kasoku += 0.5;
	//	if (keifou_saiz > point) {
	//		keifou_saiz = point;
	//		kasoku = 0.0;
	//	}
	//}
	//if (keifou_saiz >= 0.95) {
	//	keifou_saiz = 0.95;
	//} 
	hm_sprite.SetMulColor({ 1.0f,1.0f,1.0f,1-HP_saiz});// (CVector3::Zero, CQuaternion::Identity, { 1.0f,1.0f,1.0f }, { 0.5f,0.5f });
	hy_sprite.Update(CVector3::Zero, CQuaternion::Identity, { 0.5f,0.5f,1.0f }, { 0.5f,0.5f });
}
void Geizi::PostRender(CRenderContext& rc)
{
	if (player->getcamera_f())
	{
		hm_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
		hy_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
}