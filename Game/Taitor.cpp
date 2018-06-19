#include "stdafx.h"
#include "Taitor.h"
#include"Player.h"
#include"Game.h"

Taitor::Taitor()
{
}
Taitor::~Taitor()
{
}
bool Taitor::Start()
{
	//n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
	//n_sprite.Init(n_texture, 1280, 720);
	//n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
	fase = FindGO<Fade>("Fade");
	player= FindGO<Player>("Player");
	//y_texture.CreateFromDDSTextureFromFile(L"sprite/yaji.dds");
	//y_sprite.Init(y_texture, 100, 50);
	//y_sprite.Update(n_position, Quaternion, { 1.0f,1.0f,1.0f });
	Pboneforward = { 0.0f,7000.0f,5000.0f };
	//	fase->StartFadeOut();
	return true;
}
void Taitor::Update()
{
	if (fase->toumeiodo >= 1.0f) {
		if (Triggeer >= 1) {
			if (Triggeer >= 2) {

			}
			else {
				n_texture.CreateFromDDSTextureFromFile(L"sprite/waku.dds");
				n_sprite.Init(n_texture, 1500, 1000);
				Quaternion.SetRotation(CVector3::AxisZ, 90);
				fase->StartFadeIn();
			}
		
		}
		else {
			n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
			n_sprite.Init(n_texture, 1280, 720);
			fase->StartFadeIn();
		}
	}
	if (fase->toumeiodo <= 0.0f&&Triggeer >= 1) {
		if (Pad(0).GetLStickXF() < 0.0&&Target < 1) {
			n_position.x -= 100.00f;
			Target = 3;
			hyouji = 1;
			taim = 0;
		}if (Pad(0).GetLStickXF() > 0.0&&Target > 0) {
			n_position.x += 100.00f;
			Target = 0;
			hyouji = 0;
			taim = 0;
		}
	}
	if (Pad(0).IsTrigger(enButtonA)&& fase->toumeiodo <= 0.0f) {
	//	fase->StartFadeOut();
		furag = push;
		Triggeer++;
	}
	if (Pad(0).IsTrigger(enButtonB) && fase->toumeiodo <= 0.0f) {
		if(Triggeer>=1)
		fase->StartFadeOut();
		Triggeer=0;
	}

//	y_sprite.Update(n_position, Quaternion,{ 1.0f,1.0f,1.0f });
	if (furag == suii) {
		Pboneforward *= 0.98;
	}
	if (furag == push) {
		Pboneforward *= 0.98;
		target=player->Getbonepos();
		Pboneforward += target;
		furag = suii;
	//	UP = player->Getboneup();
	}
	
	if (Pboneforward.Length() <= 200.0f)
	{
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
	Crot.SetRotationDeg(UP, 2.0f);
	Crot.Multiply(Pboneforward);

	MainCamera().SetTarget(target);
	MainCamera().SetNear(1.0f);
	//MainCamera().SetUp(Getboneup());
	MainCamera().SetFar(50000.0f);
	MainCamera().SetPosition(Pboneforward);
	MainCamera().Update();
}

