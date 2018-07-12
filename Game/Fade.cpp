#include "stdafx.h"
#include "Fade.h"


Fade::Fade()
{
}


Fade::~Fade()
{
}
bool Fade::Start()
{
	m_texture.CreateFromDDSTextureFromFile(L"sprite/Fade.dds");
	m_sprite.Init(m_texture, 1280,780/*GraphicsEngine().Get2DSpaceScreenWidth(),GraphicsEngine().Get2DSpaceScreenHeight()*/);
	return true;
}
void Fade::Update()
{
	switch (m_Fade) {
	case FadeIn:
		toumeiodo -=1.0f*GameTime().GetFrameDeltaTime();
		if (toumeiodo <= 0.0f) {
			toumeiodo = 0.0f;
			m_Fade = Idle;
		}
		break;
	case FadeOut:
		toumeiodo += 1.0f*GameTime().GetFrameDeltaTime();
		if (toumeiodo >= 1.0f) {
			toumeiodo = 1.0f;
			m_Fade = Idle;
		}
		break;
	case Idle:
		break;
	}
}
void Fade::PostRender(CRenderContext& rc)
{
	if (toumeiodo > 0.0f) {
		m_sprite.SetMulColor({ 1.0f, 1.0f, 1.0f, toumeiodo });
		m_sprite.Draw(rc, MainCamera2D().GetViewMatrix(), MainCamera2D().GetViewProjectionMatrix());
	}
}
