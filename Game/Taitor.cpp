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
	return true;
}
void Taitor::Update()
{
	if (fase->toumeiodo >= 1.0f) {
		NewGO<Game>(0, "Game");
		DeleteGO(this);
	}
	if (Pad(0).IsTrigger(enButtonA)) {
		fase->StartFadeOut();
	}
}
void Taitor::Render(CRenderContext& rc)
{
	n_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetProjectionMatrix());
}
