#pragma once
#include"Fade.h"
class Taitor : public IGameObject
{
public:
	Taitor();
	~Taitor();
	bool Start();
	void Update();
	void Render(CRenderContext& rc);
	Fade* fase;
	CSprite n_sprite;				//スプライト（中身）。
	CShaderResourceView n_texture;	//テクスチャ。*/
	CVector3 n_position = CVector3::Zero;
};

