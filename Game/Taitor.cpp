#include "stdafx.h"
#include "Taitor.h"
#include"Game.h"


Taitor::Taitor()
{
}
Taitor::~Taitor()
{
}
bool Taitor::Start()
{
	n_texture.CreateFromDDSTextureFromFile(L"sprite/ge-ji.dds");
	n_sprite.Init(n_texture, 1280, 720);
	n_sprite.Update(n_position, CQuaternion::Identity, { 1.0f,1.0f,1.0f });
	fase = FindGO<Fade>("Fade");
	y_texture.CreateFromDDSTextureFromFile(L"sprite/yaji.dds");
	y_sprite.Init(y_texture, 100, 50);
	y_sprite.Update(n_position, Quaternion, { 1.0f,1.0f,1.0f });
	//	fase->StartFadeOut();
	return true;
}
void Taitor::Update()
{
	if (fase->toumeiodo >= 1.0f) {
		if (Triggeer >= 1) {
			if (Triggeer >= 2) {
				NewGO<Game>(0, "Game")->stag = Target;
				DeleteGO(this);
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
		if (Pad(0).GetLStickXF() < 0.0&&Target > 0) {
			n_position.x -= 100.00f;
			Target--;
			hyouji = 
			taim = 0;
		}if (Pad(0).GetLStickXF() > 0.0&&Target < 1) {
			n_position.x += 100.00f;
			Target++;
			hyouji = 0;
			taim = 0;
		}
	}
	if (Pad(0).IsTrigger(enButtonA)&& fase->toumeiodo <= 0.0f) {
		fase->StartFadeOut();
		Triggeer++;
	}
	if (Pad(0).IsTrigger(enButtonB) && fase->toumeiodo <= 0.0f) {
		if(Triggeer>=1)
		fase->StartFadeOut();
		Triggeer=0;
	}

	y_sprite.Update(n_position, Quaternion,{ 1.0f,1.0f,1.0f });

}
void Taitor::Render(CRenderContext& rc)
{
	n_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	if (hyouji++ <= 10) {
		y_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
	}
	else
	{
		if (taim++ >= 10) {
			hyouji = 0;
			taim = 0;
		}
	}
}
